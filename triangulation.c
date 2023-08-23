#include<stdio.h>
#include<math.h>
float to_radians();
float get_watchtowers_distance();
float get_boat_distance(const float, const int, const int);

int main(){
int x1, x2, y1, y2, alpha, beta, cx, cy,x ,y;
float d, distance, a, b, strana;
scanf("%d ", &x1);
scanf("%d ", &y1);
scanf("%d ", &alpha);
scanf("%d ", &x2);
scanf("%d ", &y2);
scanf("%d ", &beta);
distance = get_watchtowers_distance(x1, y1, x2, y2);
d = get_boat_distance(distance, alpha, beta);
strana = d / sin(to_radians(alpha));
a = sqrt(pow(strana, 2) - pow(d, 2));
b = distance - a;
x = x1 + (a * (x2 - x1) / distance);
if(y2 > y1){
      y = y1 + (a * (y2 - y1) / distance);
      cx = x + (d * (y2 - y1) / distance);
}
else {
      y = y1 + (a * (y1 - y2) / distance);
      cx = x + (d * (y1 - y2) / distance);
}
cy = y + (d * (x2 - x1) / distance);
printf("%.2f %d %d \n", d, cx, cy); 
}

float to_radians(const int angle){
    float radians = (angle * M_PI) / 180;
    return radians;
}

float get_watchtowers_distance(const int x1, const int y1, const int x2, const int y2){
      int x, y;
      x = x2 - x1;
if(y2 > y1){
      y = y2 - y1;
}
else{
      y = y1 - y2;
}
    int a = pow(x,2);
    int b = pow(y,2);
    int sucet = a + b;
    float distance = sqrt(sucet);
    return distance;
}

float get_boat_distance(const float d, const int alpha, const int beta){
    float radians_alpha = to_radians(alpha);
    float radians_beta = to_radians(beta);
    float strana = d * (sin(radians_alpha) * sin(radians_beta) / (sin(radians_alpha + radians_beta)));
    return strana;
}
