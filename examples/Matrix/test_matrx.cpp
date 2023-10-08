#include <Arduino.h>

#include <EmbedMatrix.h>


void setup() {
  Serial.begin(115200);
  delay(1000);
}


void print_mat(int r, int c, float* m)
{
  Serial.println("[");
  for(int i=0; i<r; i++)
  {
    Serial.print("[ ");
    for(int j=0; j<c; j++)
    {
      Serial.print(m[i*c+j]); Serial.print(" ");
    }
    Serial.println(" ]");
  }
  Serial.println("]");
}


void loop() {

  float data[9] = {
      1.0, 2.0, 3.0,
      4.0, 5.0, 6.0,
      10.0, 8.0, 9.0};
  float tmp[4] = {
      0.0, 0.0,
      0.0, 0.0
  };

  try {
    Embed::Matrix<float, 3, 3> a(data);
    Embed::Matrix<float, 3, 3> b(data);
    Embed::Matrix<float, 3, 3> m;
    Embed::Matrix<float, 3, 3> n;
    Embed::Matrix<float, 2, 2> c;
    Embed::Matrix<float, 3, 3> a_inv;

    Serial.println("a = "); Serial.println(a);

    Serial.print("a*2 = "); Serial.println(a * 2);

    Serial.print("|a| = "); Serial.println(a.determinant());

    Serial.print("a^11 = "); Serial.println(a.cofactor(1, 1));
    
    Serial.print("a-1 = "); Serial.println(a.invert());

  }
  catch(std::exception & ex)
  {
    Serial.println(ex.what());
  }

  delay(1000);
}
