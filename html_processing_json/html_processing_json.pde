//para conectar processing con arduino
import processing.serial.*;

Serial port; // clase serial y declaro objeto.

String string;// para recibir la data
void setup() { 
  size(800, 600); 
  background(0);
  port=new Serial(this, "COM3", 9600); // open the serial port
  // println(Serial.list());
  port.bufferUntil('\n');// buffer the serial input until it sees a newline character
}

void draw() {



  String[] lines = loadStrings("https://taller5.ludic.cc/artimanias/c_status.php");

  String jsonFragment = lines[0]; 

  JSONObject json = JSONObject.parse(jsonFragment);

  String instalacion = json.getString("instalacion");
  int opcion1 = json.getInt("opcion1"); 
  int opcion2 = json.getInt("opcion2");

  println(instalacion);
  println(opcion1);
  println(opcion2);
 
  port.write(opcion2);
  if (keyPressed) { 
    String[] cero = loadStrings("https://taller5.ludic.cc/artimanias/c_zero.php");
  }
  
  if(opcion1>opcion2){
     port.write("izquierda");
  }
  
  
  if(opcion2>opcion1){
     port.write("derecha");
  }
}
//-------------
//if (mousePressed) { 
//   String[] cero = loadStrings("http://taller5.ludic.cc/artimanias/c_zero.php");
// }
// if (keyPressed) {
//   String[] lines = loadStrings("http://taller5.ludic.cc/artimanias/c_status.php");

//   String jsonFragment = lines[0]; 

//   JSONObject json = JSONObject.parse(jsonFragment);

//   String instalacion = json.getString("instalacion");
//   int opcion1 = json.getInt("opcion1"); 
//   int opcion2 = json.getInt("opcion2");
//   println(instalacion);
//   println(opcion1);
//   println(opcion2);
// }
