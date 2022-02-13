#include "md-simul.h"

void initial_conditions(Particle & body)
{
  body.Ry = 1.6598;
  body.Vx = 0.23698;

  body.rad = 0.235;
  body.mass = 0.29698;
  body.energy = body.mass*G*1.6598 + (body.mass*0.23698*0.23698)/2;
}

void compute_force(Particle & body)
{
  // reset force
  body.Fx = body.Fy = body.Fz = 0.0;

  // gravitational force
  body.Fy += body.mass*G;

  //mechanical energy
  double delta = 0.0;
  if (delta <= 0){
  body.energy += (body.mass)*G*body.Ry + (body.mass*body.Vx*body.Vx)/2 + (body.mass*body.Vy*body.Vy)/2;
  }
  //delta E
  body.deltaE = std::abs((body.energy - body.mass*G*1.6598 - (body.mass*0.23698*0.23698)/2)/(body.mass*G*1.6598 + (body.mass*0.23698*0.23698)/2));

  // floor
  delta = body.rad - body.Ry;
  if (delta > 0) {
    body.Fy += K*delta;
    body.energy += K*(delta*delta)/2 + (body.mass*body.Vx*body.Vx)/2 + (body.mass*body.Vy*body.Vy)/2;
  }

  // Right wall
  delta = body.Rx + body.rad - LR;
  if (delta > 0) {
    body.Fx -= K*delta;
    body.energy += K*(delta*delta)/2; //+ (body.mass*body.Vx*body.Vx)/2 + (body.mass*body.Vy*body.Vy)/2;
  }

  // Left wall
  delta = LL - body.Rx + body.rad;
  if (delta > 0) {
    body.Fx += K*delta;
    body.energy += K*(delta*delta)/2; //+ (body.mass*body.Vx*body.Vx)/2 + (body.mass*body.Vy*body.Vy)/2;
  }
}

void print(Particle & body, double time)
{
  std::cout << time << "  "
            << body.Rx << "  "
            << body.Ry << "  "
            << body.Rz << "  "
            << body.Vx << "  "
            << body.Vy << "  "
            << body.Vz << "  "
            << body.deltaE << "  "
            << "\n";
}
