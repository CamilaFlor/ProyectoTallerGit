void configurarTimer(int secs) {
  String s = String(secs);
  String path  = "/artimanias/robot/comienzaTimer.php?tiempoEspera=" + s;
  // send the GET request
  Serial.println("seteando el timer");
  client.get(path);

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
}

int obtenerDecision() {
  String path  = "/artimanias/robot/estado.php";
  // send the GET request
  Serial.println("obteniendo el estado");
  client.get(path);

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

/*
    Typical response is:
    {instalacion:"robot",
    opcion1:1,
    opcion2:4,
    ...
    }

    You want "content": numberValue
  */
  int op1Start = response.indexOf("opcion1:")+8;
  int op1End = response.indexOf(",opcion2");
  String op1content = response.substring(op1Start, op1End);
  int op1 = op1content.toInt();

  int op2Start = response.indexOf("opcion2:")+8;
  int op2End = response.indexOf(",opcion3");
  String op2content = response.substring(op2Start, op2End);
  int op2 = op2content.toInt();
  Serial.print("op1:");
  Serial.println(op1);
  Serial.print("op2:");
  Serial.println(op2);

  return (op1<op2)?0:1;
}

void ponerEnCero() {
  String path  = "/artimanias/robot/ponerEnCero.php";
  // send the GET request
  Serial.println("poniendo en cero");
  client.get(path);

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
}
