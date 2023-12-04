#include <iostream>
#include <chrono>
#include "Emitter.h"
#include <fmt/format.h>
#include <filesystem>
#include "PointVizWriter.h"

int main()
{
  std::cout<<"Particle System\n";
  Emitter e(Vec3(0,0,0),20);
  pv::PointVizWriter out("Particle.csv");
  for(int i=0; i<100; ++i)
  {
      out.setFrame(i);
      e.writePV(out);
      e.update();
  }
  return EXIT_SUCCESS;
}