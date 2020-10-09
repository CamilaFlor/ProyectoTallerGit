// importa librerias para ser tipo "web" y conectarse con lo json
import java.net.*;
import java.io.*;

//conexion con arduino
import processing.serial.*;

Serial ModuloHC05; // objeto serial para conexion con arduino x blue
String dato; //que recibe de arduino 

//-------para el contador
int begin; 
int duration = 10;
int time = 10;

//--

URL url;

void setup() { 
  size(800, 600); 
  background(0);

  ModuloHC05=new Serial(this, Serial.list()[3], 9600); //inicializar puerto serial
  printArray(Serial.list());//para saber cual puerto es, lista los puertos disponibles

  begin = millis(); //para el contador
}


void draw() {
  //-------recibir los datos enviados por blue
  if (ModuloHC05.available()>0) {//si hay algun dato que este recibiendo
    dato=ModuloHC05.readString(); //lo lee y carga en 'dato'

    if (dato== "bifurcacion") { //si en el dato que manda arduino le avisa a processing que frenó

      //------cuenta 10 segundos - tiempo de votacion- y despues lee el STATUS

      if (time > 0) {  
        time = duration - (millis() - begin)/1000;
      } else {
        String lines = getJSON("https://taller5.ludic.cc/artimanias/c_status.php");  //carga json
        println(lines);
        JSONObject json = parseJSONObject(lines);

        String instalacion = json.getString("instalacion");
        int izquierda = json.getInt("opcion1"); //carga el resultado en variable
        int derecha = json.getInt("opcion2");//carga el resultado en variable


        println(instalacion);
        println(izquierda);
        println(derecha);

        //--------Analiza el resultado y hace envio de datos a arduino. 
        if (izquierda>derecha) { //gana izquierda
          //manda un dato string por blue a arduino  'izquierda'
          ModuloHC05.write('I');
        }

        if (izquierda<derecha) { //gana derecha
          //manda un dato string por blue a arduino 'derecha'
          ModuloHC05.write('D');
        }
      }
      println(getJSON("https://taller5.ludic.cc/artimanias/c_zero.php")); //despues pone en 0 los valores de la votacion.
    }
  }
}


//-------------------para que no haya problema al leer el JSon 
String getJSON(String surl) {
  String htmlText = "";
  try {
    // Create a URL object
    URL url = new URL(surl);
    URLConnection conn = url.openConnection();
    conn.setRequestProperty("User-Agent", "Mozilla/5.0 (Windows; U; Windows NT 6.1; en-GB;     rv:1.9.2.13) Gecko/20101203 Firefox/3.6.13 (.NET CLR 3.5.30729)");
    // Read all of the text returned by the HTTP server
    BufferedReader in = new BufferedReader
      (new InputStreamReader(conn.getInputStream(), "UTF-8"));

    String returnText;
    while ( (returnText = in.readLine ()) != null) {
      htmlText += returnText;
    }
    in.close();
  } 
  catch (MalformedURLException e) {
    e.printStackTrace();
  } 
  catch (IOException e) {
    e.printStackTrace();
  }
  return htmlText;
}
/*
void keyPressed() {
 String lines = getJSON("https://taller5.ludic.cc/artimanias/c_status.php");
 println(lines);
 JSONObject json = parseJSONObject(lines);
 
 String instalacion = json.getString("instalacion");
 int opcion1 = json.getInt("opcion1"); 
 int opcion2 = json.getInt("opcion2");
 
 
 println(instalacion);
 println(opcion1);
 println(opcion2);
 
 //--------Envio de datos a arduino. Resultado de votación
 if (opcion1>opcion2) { //gana izquierda
 //manda un dato por blue a arduino
 }
 
 if (opcion1<opcion2) { //gana derecha
 //manda un dato por blue a arduino
 }
 }*/
/*
void mousePressed() {
 println(getJSON("https://taller5.ludic.cc/artimanias/c_zero.php"));
 }*/
