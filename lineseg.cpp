
#include <iostream>
#include <vector>
#include <fstream>
#include "headers/lineseg.h"

// Constructor
LineSeg::LineSeg(void) {}

// Constructor that chooses random values between lower and upper.
LineSeg::LineSeg(int lower, int upper) {
  int tries = 0;
  this->x1 = random(lower,upper);
  this->y1 = random(lower,upper);
  this->x2 = random(lower,upper);
  this->y2 = random(lower,upper);

  // Make sure the line segment is not a point.
  while (this->x1 == this->x2 && this->y1 == this->y2) {
    this->x1 = random(lower,upper);
    this->y1 = random(lower,upper);
    this->x2 = random(lower,upper);
    this->y2 = random(lower,upper);
    tries++;
    if (tries > 25) {
      std::cerr << "Error: Could not generate a valid line segment in 25 tries.\n";
      exit(1);
    }
  }
  this->points.push_back(x1);
  this->points.push_back(y1);
  this->points.push_back(x2);
  this->points.push_back(y2);
  if (this->x2 - this->x1 == 0) {
    this->flag = true;
    this->slope = 0;
  }
  else {
    this->flag = false;
    this->slope = (this->y2 - this->y1) / (this->x2 - this->x1);
  }
  this->b = this->y1 - (this->slope * this->x1);
}

// Constructor to specify line segment
LineSeg::LineSeg(int a, int b, int c, int d) {
  this->x1 = a;
  this->y1 = b;
  this->x2 = c;
  this->y2 = d;
  this->points.push_back(x1);
  this->points.push_back(y1);
  this->points.push_back(x2);
  this->points.push_back(y2);
  if (this->x2 - this->x1 == 0) {
    this->flag = true;
    this->slope = 0;
  }
  else {
    this->flag = false;
    this->slope = (this->y2 - this->y1) / (this->x2 - this->x1);
  }
  this->b = this->y1 - (this->slope * this->x1);
}

// MAYBE TURN THIS RETURN INTO RETURN THIS-> POINTS
std::vector<int> LineSeg::getPoints(void) {
  return points;
}

float LineSeg::getSlope(void) {
  return slope;
}

float LineSeg::getB(void) {
  return b;
}

bool LineSeg::getFlag(void) {
  return flag;
}

bool LineSeg::intersect(LineSeg& line) {
  // Get the max and min value x and y values this line seg.
  int l1_x_max = std::max(this->x1, this->x2);
  int l1_x_min = std::min(this->x1, this->x2);
  // Get the max and min value x and y values for the input line seg.
  std::vector<int> points = line.getPoints();
  int lx1 = points[0];
  int lx2 = points[2];
  int l2_x_max = std::max(lx1,lx2);
  int l2_x_min = std::min(lx1,lx2);
  float intersect_x;
  // Test if both lines intersect at some point
  if (this->slope != line.getSlope()) {
    // Test if this LineSeg is vertical and the other LineSeg is not.
    if (this->flag == true && !(line.getFlag() == true)) {
      intersect_x = (this->b - line.getB()) / line.getSlope();
    }
    // Test if the other LineSeg is vertical and this LineSeg is not.
    else if (!(this->flag == true) && line.getFlag()== true) {
      intersect_x = (line.getB() - this->b) / this->slope;
    }
    else {
      intersect_x = (this->b - line.getB()) / (line.getSlope() - this->slope);
    }


    // Now test if intersection occurs within both LineSeg
    if (intersect_x <= l1_x_max && intersect_x <= l2_x_max &&
        intersect_x >= l1_x_min && intersect_x >= l2_x_min) {
        return true;
    }
  }
  return false;
}


bool LineSeg::overlap(LineSeg& line) {
  // Get the max and min value x and y values this line seg.
  int l1_x_max = std::max(this->x1, this->x2);
  int l1_x_min = std::min(this->x1, this->x2);
  int l1_y_max = std::max(this->y1, this->y2);
  int l1_y_min = std::min(this->y1, this->y2);

  // Get the max and min value x and y values for the input line seg.
  std::vector<int> points = line.getPoints();
  int lx1 = points[0];
  int ly1 = points[1];
  int lx2 = points[2];
  int ly2 = points[3];
  int l2_x_max = std::max(lx1,lx2);
  int l2_x_min = std::min(lx1,lx2);
  int l2_y_max = std::max(ly1,ly2);
  int l2_y_min = std::min(ly1,ly2);

  // If both lines are vertical.
  if (this->flag && line.getFlag()) {
    // If both vertical lines share the same x value.
    if (this->x1 == l1_x_max) {
      // Both lines overlap and are equal. Or, l1 encompasses l2.
      if (l1_y_max >= l2_y_max && l1_y_min <= l2_y_min) {
        return true;
      }
      // l2 encompasses l1.
      else if (l1_y_max < l2_y_max && l1_y_min > l2_y_min) {
        return true;
      }
      // l1 and l2 overlap from the top.
      else if (l1_y_max == l2_y_max) {
        return true;
      }
      // l1 and l2 overlap from the bottom.
      else if (l1_y_min == l2_y_min) {
        return true;
      }
      // l2 and l2 overlap
      else if (l1_y_max > l2_y_max && l1_y_min < l2_y_max) {
        return true;
      }
      // l2 and l2 overlap
      else if (l2_y_max > l1_y_max && l2_y_min < l1_y_max) {
        return true;
      }
      // l1 and l2 do not overlap.
      else if (l1_y_min > l2_y_max || l2_y_min > l1_y_max) {
        return false;
      }
    }
    // x coordinates are not equal and thus l2 and l2 do not overlap.
    else {
      return false;
    }
  }
  // Else, if neither line is vertical.
  else {
    if (this->slope == line.getSlope() && this->b == line.getB()) {
      // l1 encompasses l2 or l1 == l2.
      if (l1_x_max >= l2_x_max && l1_x_min <= l2_x_min) {
        return true;
      }
      // l2 encompasses l1.
      else if (l1_x_max < l2_x_max && l1_x_min > l2_x_min) {
        return true;
      }
      // l1 and l2 overlap from the top.
      else if (l1_x_max == l2_x_max) {
        return true;
      }
      // l1 and l2 overlap from the bottom.
      else if (l1_x_min == l2_x_min) {
        return true;
      }
      // l2 and l2 overlap
      else if (l1_x_max > l2_x_max && l1_x_min < l2_x_max) {
        return true;
      }
      // l2 and l2 overlap
      else if (l2_x_max > l1_x_max && l2_x_min < l1_x_max) {
        return true;
      }
      // l1 and l2 do not overlap.
      else if (l1_x_min > l2_x_max || l2_x_min > l1_x_max) {
        return false;
      }
    }
    else {
      return false;
    }
  }
  // Must be the case where l1 and l2 overlap but only at a point.
  return false;
}

// Display the attributes of LineSeg
void LineSeg::printLineSeg(void) {
  std::cerr << "-------------------------------\n";
  std::cerr << "Printing line seg:\n";
  std::cerr << "x1: " << this->x1 << ", ";
  std::cerr << "y1: " << this->y1 << ", ";
  std::cerr << "x2: " << this->x2 << ", ";
  std::cerr << "y2: " << this->y2 << "\n";
  std::cerr << "flag: " << this->flag<< "\n";
  std::cerr << "y = " << this->slope<< "x + " << this->b << "\n";
  std::cerr << "-------------------------------\n";
}

// // Display the attributes of LineSeg
// void LineSeg::printLineSeg(void) {
//   std::cout << "-------------------------------\n";
//   std::cout << "Printing line seg:\n";
//   std::cout << "x1: " << this->x1 << ", ";
//   std::cout << "y1: " << this->y1 << ", ";
//   std::cout << "x2: " << this->x2 << ", ";
//   std::cout << "y2: " << this->y2 << "\n";
//   std::cout << "flag: " << this->flag<< "\n";
//   std::cout << "y = " << this->slope<< "x + " << this->b << "\n";
//   std::cout << "-------------------------------\n";
// }

// bool LineSeg::validLength(int& a, int& b, int& c, int& d) {
//   while (a == c && b == d) {
//     a = LineSeg::random(lower,upper);
//     y_a = LineSeg::random(lower,upper);
//     x_b = LineSeg::random(lower,upper);
//     y_b = LineSeg::random(lower,upper);
//     tries++;
//     if (tries > 25) {
//       std::cerr << "Error: Could not generate a valid line segment in 25 tries.\n";
//       exit(1);
//     }
//   }
// }

// Returns a random number between upper and lower: [lower,upper]
int LineSeg::random(int lower, int upper) {
  // Switch to true if lower < 0.
  bool neg_range = false;
  // For generating between -k and k
  if (lower < 0) {
    upper = 2 * upper;
    lower = 0;
    neg_range = true;
  }
  // open /dev/urandom to read
  std::ifstream urandom("/dev/urandom");
  // check that it did not fail
  if (urandom.fail()) {
      std::cerr << "Error: cannot open /dev/urandom\n";
      return 1;
  }
  // Read a random 8-bit value.
  // Have to use read() method for low-level reading
  char ch = 'a';
  urandom.read(&ch, 1);
  unsigned int rand_num = (unsigned int)ch % (upper + 1);
  // To keep track of number of loops.
  unsigned int tries = 0;
  // Add random numbers to rand_num such that rand_num
  // is greater than or equal to lower.
  while (rand_num < lower) {
    unsigned int rand_temp;
    urandom.read(&ch, 1);
    unsigned int upper_temp = upper - rand_num;
    rand_temp = (unsigned int)ch % (upper_temp + 1);
    rand_num += rand_temp;
    tries += 1;
    if (tries > 25) {
      std::cerr << "Failed to generate random number in 25 tries";
      exit(1);
    }
  }
  // For generating between -k and k
  if (neg_range) {
    rand_num = rand_num - (upper / 2);
  }
  // close random stream
  urandom.close();
  return rand_num;
}
