Serial myPort1;  // Create object from Serial class
String tempVal;     // Data received from the serial port

Serial myPort2;  // Create object from Serial class
String pressVal;     // Data received from the serial port


boolean answer = true;
boolean userAnswer;
boolean answeredQuestion = false;

void setup() {
  size(1000, 500);
  reset();
}

void draw() {
  if(tempVal > 70)
  {
    userAnswer = true;
    results();
  }
  else if(pressVal > 7)
  {
    userAnswer = false;
    results();
  }
}

void clean()
{
  background(154, 140, 152);
  fill(255);
  textSize(40);
  text("COVID stands for Corona Virus Disease", 100, 200); 
  text("TRUE / FALSE", 350, 320);
}

void reset()
{
  clean();
  answeredQuestion = false;
}

void results()
{
  clean();
  if(!answeredQuestion)
  {
    if(userAnswer == answer)
    {
      text("CORRECT! The answer was " + answer, 200, 430);
    }
  
    else
    {
      text("Aww sorry, the answer was " + answer, 200, 430);
    }
    
    answeredQuestion = true;
  }
}

void keyTyped() {
  println("typed " + int(key));
  if(answeredQuestion && !(int(key) == 32))
  {
    clean();
    text("Please hit spacebar to reset...", 200, 430);
  }
  else if(int(key) == 32)
  {
    reset();
  }
  else
  {
    clean();
    text("Please use the sensors to answer...", 200, 430);
  }
}
