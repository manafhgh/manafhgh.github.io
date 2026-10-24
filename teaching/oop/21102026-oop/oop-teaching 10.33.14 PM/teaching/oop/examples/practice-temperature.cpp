#include <iostream>
#include <stdexcept>
using namespace std;

class Temperature{
private:
   const char scale_type; //(F)ahrenheit or (C)elsius
   float reading;

public:
   Temperature();
   Temperature(char, float);
   void printT()const;
   char get_type()const;
   float get_reading()const;
   void changeT(char, float d);
};

Temperature::Temperature() :scale_type('C')
{
   reading = 0;
}

Temperature::Temperature(char t, float r)
:scale_type(t),reading(r)
{
    if (t != 'C' && t != 'F') throw invalid_argument("Use C or F");
}

void Temperature::printT() const {
   if(scale_type=='C'){
       cout << reading << " " << scale_type << endl;
       cout << reading * 9/5 + 32 << " F\n";
   }
   else{
       cout << (reading - 32) * 5/9 << " C\n";
       cout << reading << " F\n";
   }
}

char Temperature::get_type() const {
   return scale_type;
}

float Temperature::get_reading()const{
   return reading;
}

//If the scale type is 'C' and t is 'C'
//or scale type is 'F' and t is 'F'
//then just add d to the current reading
//else, convert 'd' properly then add it to
//the current reading.
void Temperature::changeT(char t, float d){
   if (t != 'C' && t != 'F') throw invalid_argument("Use C or F");
   if(t==scale_type)
       reading += d;
   else if(scale_type=='C'){ // t must be 'F'
       reading += d * 5.0f/9.0f; // A change in temperature has no 32-degree offset.
   } else{ //t must be 'C'
       reading += d * 9.0f/5.0f; // Convert the change, not an absolute reading.
   }
}


void printTemArray(const Temperature t[], int size){
   for(int i=0;i<size;i++){
       cout <<"["<<i<<"]\n";
       t[i].printT();
       cout << "-------\n";
   }
   cout << "-------\n";
}

//A non-member function to compute
//the average (in Celsius) of temperatures
//in an array of temperatures.
//The temperatures in the array could be
//a mix of Fahrenheit and Celsius readings
//so those in Fahrenheit need to be converted
float tempAvgArray(const Temperature t[],int size){
   if (size <= 0) throw invalid_argument("Average requires a nonempty array");
   float sum = 0;
   for(int i=0;i<size;i++){
       if(t[i].get_type()=='C')
           sum+=t[i].get_reading();
       else
           sum += (t[i].get_reading() - 32) * 5/9;
   }
   return sum/size;
}


int main() {
    Temperature t[2]={Temperature('C',0),Temperature('F',32)};
    t[0].changeT('F',18);
    t[1].changeT('C',10);
    printTemArray(t,2);
    cout << tempAvgArray(t,2) << " C\n";
}
