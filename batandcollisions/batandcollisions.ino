//bat move and shoot demo
#include <Arduboy2.h>
Arduboy2 arduboy;
//define constants
constexpr uint8_t maxSonics = 5; //max number of active player bullets

// Max number of active background segments
constexpr uint8_t maxBackgrounds = 10;

// Start point of new background segment
constexpr uint8_t backgroundStart = 128;

// Speed of bullets
constexpr int backgroundSpeed = 1;

// Limit of the x position of backgrounds
constexpr int backgroundXLimit = -31;

#define MAX_NUM_ENEMIES 3
#define DELAY_MODIFIER 4
#define RESTART_DELAY 300


//declare global variables here
int playerx = 5; //player x position (L<R)
float playery = 10; //player y position (U<D), is float due to fractional rate of descent
int pxupperlim =120; //player x limits
int pxlowerlim = 0;
int pyupperlim = 57; //player y limits
int pylowerlim = 0;
int pvx = 2; // player x speed
int vflap = -2;//player flap impetus
float grav = .2;  //grav force
float vglide = .8;  // rate at whic bat glides... use .5; for 60 FPS
float pvy = 1; //player vert speed...this is giving issues at 60 FPS
int vdive = 4; //player dive speed
int batsprite = 0; // 0 glide, 1 flap, 2 dive... used to animate
int currentnumsonic = 0;
int sonicspeed = 3; //speed of bullets
int sonicxlim = 130; //limit as to x position of sonics
int currentdelay = 60;
int currentenemyindex = 0;
int exlowerlim = -32;



//declare whatever else
struct Sonic {
  int x;
  int y;
  bool enabled;
  };
  
struct Background
{
  int x;
  int y;
  int spriteIndex;
};

Sonic sonic[maxSonics] = { //first "Sonic" refers to structure, second "sonic" is name of array
      { 0, 0, false}, // refer to Sonic structure. setting initial values in array of sonics. x=0, y=0, enabled = false (not active)
      { 0, 0, false}, // total of 5 for max num sonics
      { 0, 0, false},
      { 0, 0, false},
      { 0, 0, false},
    };

struct EnemyList {
  int enemytype;
  int x;
  int y;
  int delaynext; //should count DOWN one unit per frame
  bool enabled;
  int modA; //changes function based on etype
  int modB;
};

EnemyList enemyList[MAX_NUM_ENEMIES] = {
  { 0, 127, 32, 300, false , 0, 32 },
  { 0, 127, 15, 150, false, 0, 15 },
  { 0, 127, 48, 122, false, 0, 48 },
};

// First "Background" refers to structure, second "background" is name of array
Background background[maxBackgrounds]
{
  // Refer to Background structure. setting initial values in array of backgrounds. x=0, y=0, srpite index, flip = false (true for ceiling only)
  // Total of 10 for maxBackgrounds (5 floor, 5 ceiling)
  { 0, 55, 0},
  { 32, 55, 0},
  { 64, 55, 0},
  { 96, 55, 0},
  { 128, 55, 0},
  { 0, 0, 0},
  { 32, 0, 0},
  { 64, 0, 0},
  { 96, 0, 0},
  { 128, 0, 0},
};
//sprites
const unsigned char PROGMEM batflap[] = 
{
// width, height,
16, 8,
0x40, 0x60, 0x60, 0x60, 0x70, 0x30, 0x1f, 0x3e, 0x36, 0x3f, 0x16, 0x30, 0x70, 0x70, 0x60, 0x40, 
};

const unsigned char PROGMEM batglide[] =
{
// width, height,
16, 8,
0x02, 0x06, 0x06, 0x0e, 0x0e, 0x0c, 0x3e, 0x7c, 0x6c, 0x7e, 0x2c, 0x0e, 0x0e, 0x0e, 0x06, 0x02, 
};

const unsigned char PROGMEM batdive[] =
{
// width, height,
8, 16,
0x00, 0x80, 0xe0, 0x00, 0xc0, 0x00, 0x00, 0x00, 
0x00, 0x1f, 0x7f, 0xf8, 0xdf, 0xff, 0x58, 0x00, 
};

const unsigned char PROGMEM sonicbullet[] =
{
// width, height,
4, 4,
0x06, 0x09, 0x09, 0x06, 
};

//sprites for background
const unsigned char flat[] PROGMEM
{
  // width, height,
  32, 9,
  0x80, 0x40, 0xa0, 0x40, 0x80, 0x40, 0x80, 0x40, 0xa0, 0x40, 0xa0, 0x40, 0xa0, 0x50, 0x80, 0x40, 0xa0, 0x40, 0xa0, 0x40, 0xa0, 0x50, 0xa0, 0x40, 0xa0, 0x40, 0x80, 0x40, 0xa0, 0x40, 0xa0, 0x40, 
  0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 
};

const unsigned char PROGMEM spikeleft[] =
{
// width, height,
32, 9,
0x40, 0xa0, 0x50, 0xaa, 0x55, 0xaa, 0x50, 0x80, 0x40, 0xa0, 0x40, 0xa0, 0x40, 0x80, 0x40, 0x80, 0x40, 0xa0, 0x40, 0xa0, 0x40, 0x80, 0x00, 0xa0, 0x40, 0xa0, 0x50, 0xa0, 0x50, 0xa0, 0x50, 0xa0, 
0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 
};

const unsigned char PROGMEM spikeright[] =
{
// width, height,
32, 9,
0x40, 0xa0, 0x40, 0x80, 0x00, 0x80, 0x00, 0x80, 0x40, 0xa0, 0x40, 0xa0, 0x40, 0xa0, 0x50, 0xa0, 0x50, 0xa0, 0x40, 0xa0, 0x40, 0xa0, 0x50, 0xa0, 0x50, 0xa0, 0x50, 0xaa, 0x55, 0xaa, 0x54, 0xa0, 
0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 
};
    //ceiling
const unsigned char PROGMEM flatup[] =
{
// width, height,
32, 9,
0x02, 0x05, 0x0a, 0x05, 0x02, 0x05, 0x02, 0x05, 0x0a, 0x05, 0x0a, 0x05, 0x0a, 0x15, 0x02, 0x05, 0x0a, 0x05, 0x0a, 0x05, 0x0a, 0x15, 0x0a, 0x05, 0x0a, 0x05, 0x02, 0x05, 0x0a, 0x05, 0x0a, 0x05, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM spikeleftup[] =
{
// width, height,
32, 9,
0x05, 0x0a, 0x15, 0xaa, 0x55, 0xaa, 0x15, 0x02, 0x05, 0x0a, 0x05, 0x0a, 0x05, 0x02, 0x05, 0x02, 0x05, 0x0a, 0x05, 0x0a, 0x05, 0x02, 0x01, 0x0a, 0x05, 0x0a, 0x15, 0x0a, 0x15, 0x0a, 0x15, 0x0a, 
0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM spikerightup[] =
{
// width, height,
32, 9,
0x05, 0x0a, 0x05, 0x02, 0x01, 0x02, 0x01, 0x02, 0x05, 0x0a, 0x05, 0x0a, 0x05, 0x0a, 0x15, 0x0a, 0x15, 0x0a, 0x05, 0x0a, 0x05, 0x0a, 0x15, 0x0a, 0x15, 0x0a, 0x15, 0xaa, 0x55, 0xaa, 0x55, 0x0a, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM crowflap[] =
{
// width, height,
15, 8,
0x00, 0x00, 0x00, 0x04, 0x04, 0xae, 0xfa, 0x0e, 0x3e, 0xec, 0xac, 0x88, 0x08, 0x00, 0x00, 
};

const unsigned char PROGMEM crowglide[] =
{
// width, height,
15, 7,
0x01, 0x01, 0x0b, 0x09, 0x1f, 0x16, 0x5c, 0x5c, 0x3e, 0x1b, 0x13, 0x11, 0x03, 0x01, 0x01, 
};

//runs once on startup
void setup() {
  arduboy.begin();
  arduboy.clear();
  arduboy.setFrameRate(30); //TBD if 60 frames or 30
  
}

//runs continuously 
void loop() {
  

  //Prevent the Arduboy from running too fast
  if (!arduboy.nextFrame()) {
    return;
  }

  arduboy.clear();
  arduboy.pollButtons(); //magic incantation for justPressed etc.

  updateBackgrounds();
  drawBackgrounds();
  enemyspawn();
  updateenemies();
  batfire();
  updateSonics();
  bat();
  drawbat();
  increaseDifficulty(); 

  
  arduboy.display();
}




void bat(){
  batsprite = 0; //set batspr to glide, here to prevent sticky sprites
  
  if (arduboy.pressed(LEFT_BUTTON)) { //move left
    playerx = playerx - pvx;
    if (playerx < pxlowerlim){
        playerx = pxlowerlim;//prevent movement offscreen
    }
  }
  if (arduboy.pressed(RIGHT_BUTTON)) { //move right
    playerx = playerx + pvx;
    if (playerx > pxupperlim){
        playerx = pxupperlim;
    }
  }
  if (pvy < vglide){ //if vert speed is LESS THAN glide speed
    pvy = pvy + grav; //increase vert speed by grav force (positive is down)
  }
  if (pvy > vglide){ // if vert speed GREATER THAN glide speed
    pvy = vglide; //slow to glide sped instantly
  }
 
  if (arduboy.justPressed(A_BUTTON)) { //flapping, note JUSTPRESSED
    pvy = vflap; //make vert speed equal flap speed
    batsprite = 1; //change sprite
  }
  if (arduboy.pressed(DOWN_BUTTON)) { //dive
    pvy = vdive; //note vdive is greater than vglide
    batsprite = 3;
  }
   playery = playery + pvy; //must be AFTER dive check, or dive would be negated by glide checks
  if (playery > pyupperlim){
    playery = pyupperlim; //prevent moving offscreen
  }
  else if (playery <pylowerlim){
     playery = pylowerlim; //prevent moving offscreen
  }
}

void drawbat(){
  //Draw player sprite
  if (batsprite == 0){ //For whatever reason, could not get a switch statement to work!!!
      Sprites::drawSelfMasked(playerx, playery, batglide, 0);
  }
  else if (batsprite == 1){
      Sprites::drawSelfMasked(playerx, playery, batflap, 0);
  }
  else if (batsprite == 3){
      Sprites::drawSelfMasked(playerx + 4, playery - 9, batdive, 0); //this sprite is differently shaped, hence position modifiers
  }
}

void fireSonics(int sonicnumber) {
  sonic[sonicnumber].y = playery + 3;
  sonic[sonicnumber].x = playerx + 8;
  sonic[sonicnumber].enabled = true;
  
}

void batfire() {
   if (arduboy.justPressed(B_BUTTON)) { //shooting, note JUSTPRESSED
    if (currentnumsonic < maxSonics){ //if less bulets active than max
       for (uint8_t i = 0; i < maxSonics; i++) { //this loop finds first inactive slot in sonic array

        if (!sonic[i].enabled) {  //if disabled,
          fireSonics(i); //fire new bullet (item i in array)
          break;
        }
       currentnumsonic++; //add to count of bullets
    }
 }}}
void updateSonics() {

  for (byte i = 0; i < maxSonics; i++) {
        
    if (sonic[i].enabled == true) {

      Sprites::drawSelfMasked(sonic[i].x, sonic[i].y, sonicbullet, 0);
      sonic[i].x = sonic[i].x + sonicspeed; //move sonic to right
    }
          

      if (sonic[i].x > sonicxlim) {
        sonic[i].enabled = false;
        currentnumsonic--; 
      }
   
    }
        
  }

void updateBackgrounds() //Corrected by Pharap. Thank you!!!
{
  for (uint8_t index = 0; index < maxBackgrounds; ++index)
  {
    
      // Move background left
      background[index].x -= backgroundSpeed;

      
      if (background[index].x < backgroundXLimit)
      { 
        int imageIndex = random(0, 3);
        background[index].x = backgroundStart;
        background[index].spriteIndex = imageIndex;
        
      }
    
  }
}

void drawBackgrounds() //could maybe implement sprite rotation for savings? 
{
  for (uint8_t index = 0; index < maxBackgrounds; ++index)
  {
    if (index < (maxBackgrounds/2)){
      if (background[index].spriteIndex == 0){
        Sprites::drawOverwrite(background[index].x, background[index].y, flat, 0); //change flat to sprite index
      }
      else if (background[index].spriteIndex == 1){
        Sprites::drawOverwrite(background[index].x, background[index].y, spikeleft, 0); //change flat to sprite index
      }
      else if (background[index].spriteIndex == 2){
        Sprites::drawOverwrite(background[index].x, background[index].y, spikeright, 0); //change flat to sprite index
      } 
    }
    else {
      if (background[index].spriteIndex == 0){
        Sprites::drawOverwrite(background[index].x, background[index].y, flatup, 0); //change flat to sprite index
      }
      else if (background[index].spriteIndex == 1){
        Sprites::drawOverwrite(background[index].x, background[index].y, spikeleftup, 0); //change flat to sprite index
      }
      else if (background[index].spriteIndex == 2){
        Sprites::drawOverwrite(background[index].x, background[index].y, spikerightup, 0); //change flat to sprite index
      }
    }
  }
}


void enemyspawn(){
  if (currentdelay > 0){
    currentdelay--;
  }
  else if (currentdelay == 0){ //must be ==0. -1 will halt list progression until boss defeated
    enemyList[currentenemyindex].enabled = true;
    currentdelay = enemyList[currentenemyindex].delaynext;
    currentenemyindex++;
  }
}

void updateenemies(){
  for (uint8_t i =0; i <MAX_NUM_ENEMIES; i++){
    if (enemyList[i].enabled == true){
      if (enemyList[i].enemytype == 0){
        crow(i);
      }
     
      
    }
  }
}

uint8_t getImageHeight(const uint8_t *image) { //filmote

  return pgm_read_byte(image + 1);

}

bool collisionSonic (int enemyX, int enemyY, unsigned char PROGMEM enemySprite) { //adapted from filmote
    
  for (uint8_t i = 0; i < maxSonics; i++) {

    if (sonic[i].enabled == true) {

      if (collide(enemyX, enemyY - getImageHeight(enemySprite), enemySprite, sonic[i].x, sonic[i].y - getImageHeight(sonicbullet), sonicbullet)) {

        sonic[i].enabled = false;
        return true;
          
      }
      
    }
    
  }

  return false;
 
}

void enemyReset(int i){
  enemyList[i].x = 130;
  enemyList[i].y = 8*random(1,7);
  enemyList[i].modB = enemyList[i].y;
  enemyList[i].delaynext = enemyList[i].delaynext / DELAY_MODIFIER;
  enemyList[i].enabled = false;
}

void destroyEnemy(int i){ //can be updated to include a death anim?
  enemyReset(i);
}

void drawcrow(int i, int crowsprite){
  //Draw player sprite
  if (crowsprite == 0){ 
      Sprites::drawSelfMasked(enemyList[i].x, enemyList[i].y, crowglide, 0);
  }
  else if (crowsprite == 1){
      Sprites::drawSelfMasked(enemyList[i].x, enemyList[i].y, crowflap, 0);
  }
  
}



void crow(int i){

  int crowsprite = 1;
  int crowvx = 1;
  int crowvglide = 1;
  int grav = 1;
  int crowvflap = -4;
  
  if (enemyList[i].modA>0){
    crowsprite = 0; //set crowspr to glide, here to prevent sticky sprites ---could be local sprite
  }
  

  enemyList[i].x = enemyList[i].x-crowvx; //move left
  
    
  if (enemyList[i].modA < crowvglide){ //if vert speed is LESS THAN glide speed---crow vglide could be local
    enemyList[i].modA = enemyList[i].modA + grav; //increase vert speed by grav force (positive is down)---grav could be local
  }
  
 
  if (enemyList[i].y > enemyList[i].modB) { //flapping, note JUSTPRESSED
    enemyList[i].modA = crowvflap; //make vert speed equal flap speed -- crowvflap local?
    crowsprite = 1; //change sprite
  }
  
  enemyList[i].y = enemyList[i].y + enemyList[i].modA; //must be AFTER dive check, or dive would be negated by glide checks
  if (crowsprite == 1){
    if (collisionSonic(enemyList[i].x, enemyList[i].y, crowflap)){
      destroyEnemy(i);
    }
  }
  else{
    if(collisionSonic(enemyList[i].x, enemyList[i].y, crowglide)){
      destroyEnemy(i);
    }
  }
  drawcrow(i, crowsprite);

  if (enemyList[i].x < exlowerlim){ //reset enemy when it moves offscreen
    enemyReset(i);    
  }
  
}

void increaseDifficulty(){
  if (currentenemyindex == MAX_NUM_ENEMIES){
    currentdelay = RESTART_DELAY;
    currentenemyindex = 0;
  }
}
