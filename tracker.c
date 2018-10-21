/* John Ragan Harrison - Tracking Code 2 - ECE 209 - 3/29/2018.

Prefers grading on EOS Linux.

The program takes in a time, x, and y input and calculates the distance from
the given input to a nearest road denoted by a slope and a y-intercept.
The program then calculates the total distance along these roads between two points,
the number of changes in a road, the change in direction, and the maximum speed between two
points on any road.

*/


#include <stdio.h> //Including stdio.h for scanf and printf functions as well as math.h for pow and sqrt functions.
#include <math.h>

#ifndef SECRET_TESTS
double M1=-1.0, B1=0; // Road 1 slope and intercept.
double M2=1.0, B2=0;  // Road 2 slope and intercept.
#else 
// This allows Dr. Tuck to test my program easily with different roads.
double M1=SECRET_M1, B1=SECRET_B1;
double M2=SECRET_M2, B2=SECRET_B2;
#endif

int count =0; //Incraments a count variable each time the 'track' function is executed. This tells us whether or not the very first iteration is executing.
int Road=1, First_road=1; //First road decleration.
int Changed_direction=0; //Number of times a direction change is counted in the program.
int Changed_road=0; //Which road the program changes on to.
double previous_road=0.0; //Decleration to contain the value of the previous road when the next iteration is executing.
double previous_delta=0.0; //This is used to hold the previous change in delta, a variable used to tell whether or not the distance traveled by two x coordinates are positive or negative.
double delta=0.0; //Holds the current value of delta.
double Total_distance=0; //Total distance counter.
double Peak_speed=0.0; //Max speed between the various data points.
double PreviousSpeed = 0.0; //Holds the speed of the last iteration of two coordinates for comparrison with the current speed. Used to calculate the maximum speed.

void track(double time, double x, double y); //Primary function used to calculate all the variables mentioned above. Calls every other function in the program.
double distance(double x1, double y1, double x2, double y2); //Calculates the distance between two points using Pythag's Theorm.
double nearest_point_on_road(double x, double y, int road); //Calculates the nearest point on the closest road in reference to the entered x and y values.
double distance_to_road(int road, double x, double y); //Calculates the distance from an entered x and y variable to the corresponding point on the nearest road.
int closest_road(double x, double y, int road); //Find which road is actually closest to the entered point.


int main() { //Main function. Calls the 'track' function after a time, x, and y variable are inputted by the user. 
  double time, x, y; //Initializes a time, x, and y variable that will store user inputs.
  int ret;

  do {

    ret = scanf("%lf%lf%lf",&time,&x,&y); //Searches for three inputs by the user and only breaks if three are entered.
    
    if (ret==3)
      {

    track(time,x,y); //Calls the track function to calculate the total distance, peak speed, # of changes in direction, # of changes in the road, and the first and last road the "GPS" was on.
      }

  } while(ret==3); //Exit variable for the loop.

  printf("Total distance = %.2lf\n",Total_distance); //Prints out the values calculated in 'track'.
  printf("Peak speed = %.2lf\n",Peak_speed);
  printf("# of changes in direction = %d\n",Changed_direction);
  printf("# of changes in road = %d\n",Changed_road);
  printf("First Road = %d, Last Road = %d\n",First_road,Road);
  
  return 0;
}

double distance(double x1, double y1, double x2, double y2) { //Distance function. Uses the Pythagorean Theorm to calculate the distance from one coordinate to another.
  double distVal=0;

  distVal = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)); //Standard use of the Pythag. Theorm to calculate distance. Employs functions from the math.h library.
  
  return distVal; //Returns the value stored in distval to the section of the code that called the function.
}


double nearest_point_on_road(double x, double y, int road) { //Calculates the nearest point on the closest road to the x and y coordinates that were inputted by the user.

  double b=0.0; //Variable b is used the hold the y-intercept of the line equations created by M1, M2, B1, and B2.
  double xP=0.0; //xP will store the closest x value on the closest road calculated by the following equations.

if (road ==1) { //If the closest road is 1, we use M1 and B1 to calculate the b value (y-intercept) and closest x value, xP, using the equations below. These were obtained by rearranging the line equation for road 1 and setting it equal to the horizontal path from the closest point on the road to the coordinates inputted by the user. 
  b = (y + (x/M1));
  xP = ((B1 - b)/((-1.0/M1)-M1));
} else if (road ==2) { //If the closest road is 2, we use M2 and B2 to calculate the b value (y-intercept) and closest x value, xP, using the equations below. These were obtained by rearranging the line equation for road 2 and setting it equal to the horizontal path from the closest point on the road to the coordinates inputted by the user.
  b = (y + (x/M2));
  xP = ((B2 - b)/((-1.0/M2)-M2));
}
  return xP; //Closest x value on the closest road is returned to the section of the code that called the function.
}


double distance_to_road(int road, double x, double y) { //This function calculates the distance from the corrdinates inputted by the user to the closest cooresponding coordinates on the closest line.
 
  double xP =0; //xP is the returned x value located on either road1 or road2 calculated by the 'nearest_point_on_road' function.
  double yP =0; //yP will store the corresponding y value located on either road1 or road2.
  double RoadDist =0; //RoadDist will be the return the value of the distance between the inputted user coordinates and the corresponding point on either road1 or road2 that is the closest.

  xP = nearest_point_on_road(x, y, road); //calculates the x value on the nearest road.
  if (road == 1) { //If the nearest road is 1, the program then plugs the calculated x value vack into the equation to get the y value.
  yP = ((M1 * xP) + B1);
} else if (road == 2) { //If the nearest road is 2, the program then plugs the calculated x value vack into the equation to get the y value.
  yP = ((M2 * xP) + B2);
}
  RoadDist = distance(xP, yP, x, y); //The program then finds the distance by calling the distance function and using it to calculate the distance between the inputted x and y value and the nearest x and y value on the nearest road.
  return RoadDist;
}


int closest_road(double x, double y, int road) { //This program determines which road is closest to the x and y value inputted by the user.
   
   int StartingRoad = 0; //StartingRoad holds the value of the initial road for comparrison later.
   double RoadDist1 =0.0; //This value holds the calculated distance from the inputted coordinates to road 1.
   double RoadDist2 =0.0; //This value holds the calculated distance from the inputted coordinates to road 2.

   StartingRoad = road;
   road = 1;
   RoadDist1 = distance_to_road(road, x, y); //uses the 'distance_to_road' function to find the distance from the inputted x and y values to road 1.
   road = 2;
   RoadDist2 = distance_to_road(road, x, y); //uses the 'distance_to_road' function to find the distance from the inputted x and y values to road 2.

   if (RoadDist1 > RoadDist2) { //If statement to figure out which road is closest. If the distance from road 1 is less than the distance from road 2, then road 1 is the closest road. If the distance from road 2 is less, then road 2 is the closest.
    return 2;
   } else if (RoadDist2 > RoadDist1) {
    return 1;
   } else if (RoadDist1 == RoadDist2) {
    return StartingRoad;
   }
    return 0;
}


void track(double time, double x, double y) {
        static double CurrentSpeed; //Variable to hold the calculated speed of the iteration of the current two coordinates.
        static double prior_x; //Holds the prior x value claculated by the function for comparison.
        static double prior_y; //Holds the prior y value calculated by the function for comparison.
        static double new_x; //Holds the value of x currently being calculated by the function.
        static double new_y; //Holds the value of y currently being calculated by the function.
        static double intersectionX; //When changes in the current road traveled occur, the intersection point of the two roads will be calculated and the x value will be stored here.
        static double intersectionY; //When changes in the current road traveled occur, the intersection point of the two roads will be calculated and the y value will be stored here.
        static double distance1; //Holds the value of the distance from the current coordinate to the intersection point of the two roads.
        static double distance2; //Holds the value of the distance from the intersection point to the second coordinate point.

        if (count == 0) { //Used to determine if this is the first iteration of the loop. Count is iterated after the first iteration.
          First_road = closest_road(x, y, Road); //Calls the 'closest_road' function to calculate which road is closest to the inputted x and y values.
          Road = First_road;
        	prior_x = nearest_point_on_road(x, y, Road); //Calls the 'nearest_point_on_road' function to calculate the nearest x point on the Road calculated in the previous function.
        	if (Road == 1) {
					prior_y = ((M1 * prior_x) + B1); //Calculates the respective y coordinate if the closest road was Road 1.
				} else if (Road == 2) {
					prior_y = ((M2 * prior_x) + B2); //Calculates the respective y coordinate if the closest road was Road 2.
				}

    previous_road = Road; //Sets previous_road equal to the current road for future comparrison.
    count++; //Incraments count to denote that the first iteration is finished.
        	
        } else { //If this is NOT the first iteration of the program, this is the part of the function that executes.
          Road = closest_road(x, y, Road); //Calls the 'closest_road' function to calculate which road is closest to the inputted x and y values.
          new_x = nearest_point_on_road(x, y, Road); //Calls the 'nearest_point_on_road' function to calculate the nearest x point on the Road calculated in the previous function.
        	if (Road == 1) {
					new_y = ((M1 * new_x) + B1); //Calculates the respective y coordinate if the closest road was Road 1.
				} else if (Road == 2) {
					new_y = ((M2 * new_x) + B2); //Calculates the respective y coordinate if the closest road was Road 2.
				}
       
        delta = (new_x - prior_x); //Calculates delta, the distance between the previously calculated x value and the x value just calculated by the functions.

          if (((delta > 0) && (previous_delta < 0)) || ((delta < 0) && (previous_delta > 0)) || (Road != previous_road)) { //Because a change in direction must be accounted for if road changes or if a reversal is made, 'Changed_direction' must be incremented.
            Changed_direction++; //Increments if the signs of 'delta' and 'previous_delta' are different or if 'Road' is not equal to 'previous_road'.
          } else { //If none of these conditions are met, Changed_direction remains the same.
            Changed_direction = Changed_direction;
          }

          if (Road != previous_road) { //imilar to how we incramented 'Changed_direction', if 'previous_road' and 'Road' are not the same, this code will incrament the 'Changed_road' value by 1.
            Changed_road++;
            intersectionX = ((B2 - B1)/(M1 - M2)); //The program must also calculate the distance from one point to another. Because the points are on two seperate roads, we must go through the intersection point of the roads in order to find the accurate distance.
            intersectionY = ((M1*intersectionX) + B1); //The program calculates the y variable after plugging in the x variable to either one of our road equations. The above equation calculates the x variable.
            distance1 = distance(prior_x, prior_y, intersectionX, intersectionY); //The program then calculates the distance from the first point on the first road to the intersection point.
            distance2 = distance(intersectionX, intersectionY, new_x, new_y); //Afterwards, it calculates the distance from the intersection point to the second point on the second road.
            
            Total_distance = (distance1 + distance2) + Total_distance; //The total distance is the sum of these two distances plus the distances calculated in previous iterations.
            CurrentSpeed = ((distance1 + distance2) / time); //To get the current speed, the function divides the distance calculated in that iteration and divides it by the time it takes to reach the second point.  
          } else if (Road == previous_road) { //If the second road is the SAME however, all the program has to do is calculate the distance between the two points without going through the intersection.

            Total_distance = (Total_distance + distance(prior_x, prior_y, new_x, new_y)); //The total distance is then incramented.
            CurrentSpeed = (distance(prior_x, prior_y, new_x, new_y) / time); //The current speed is also found.
          }

			if (count == 1) { //This part of the function calculates the peak speed across all inputs. If count is equal to 1 (I.E. when we don't have two current speeds to compare), we just set the peak speed equal to the first current speed.
        Peak_speed = CurrentSpeed;
        PreviousSpeed = CurrentSpeed; //The previous speed is then asigned to the current speed calculated in the function.
      } else if (CurrentSpeed > Peak_speed) { //If there IS a current speak and a peak speed to compare, the function will assign the peak speed to the max of the two variables.
				Peak_speed = CurrentSpeed;
			  PreviousSpeed = CurrentSpeed;
      } else {
        PreviousSpeed = CurrentSpeed;
			}

		previous_road = Road; //At the end of the iteration, some of the current variables calculated are stored in 'previous' variables to be used in further calculations. For example, 'previous_road' gets 'Road' stored into it.
    previous_delta = delta; //'Delta' is saved into previous_delta'.
    prior_x = new_x; //'new_x' is saved into prior_x'.
		prior_y = new_y; //'new_y' is saved into 'prior_y'.

		count++; //Count is incramented.
		
		}

}