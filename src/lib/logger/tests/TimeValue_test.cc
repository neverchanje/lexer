//
// Created by neverchanje on 9/26/15.
//

#include <TimeValue.h>

using namespace std;
using namespace sugen;

int main() {

  printf("Current Time is: %s\n", TimeValue::now().toFormattedString().c_str());

  printf("Current Local Time is: %s\n", TimeValue::now().toLocalFormattedString().c_str());

}