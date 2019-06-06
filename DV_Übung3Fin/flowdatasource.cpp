#include "flowdatasource.h"
#include <math.h>
#include <algorithm>
#include <iostream>
#include <vector>

FlowDataSource::FlowDataSource()
{
    createData();
}

//To understand what is going on in this function: Every 3d point in the room has a vector of 3 values.
//Eg. Point f(x,y,z) = (a,b,c)
//          f(0,1,2) = (5.0,4.1,3.9)
void FlowDataSource::createData()
{
    cartesianDataGrid = new float[dataGridPoints*dataGridPoints*dataGridPoints*3];
    gen_tornado(dataGridPoints,dataGridPoints,dataGridPoints,1,cartesianDataGrid);
}

inline int indexOfZYXC(int z, int y, int x, int c, int ny, int nx, int nc)
{
    return z*ny*nx*nc + y*nc*nx + x*nc + c;
}

float FlowDataSource::getDataValue(int iz, int iy, int ix, int ic)
{
    return cartesianDataGrid[indexOfZYXC(iz,iy,ix,ic,dataGridPoints,dataGridPoints,3)];
}


void FlowDataSource::printValuesOfHorizontalSlice(int iz)
{
    for(int y = 0; y < dataGridPoints;y++)
    {
        for(int x = 0; x < dataGridPoints;x++)
        {
            std::cout << getDataValue(iz,y,x,3) << std::endl;
        }
    }
}

float FlowDataSource::getHighest()
{
    float max = 0;
    for (int i = 0; i< dataGridPoints*dataGridPoints*dataGridPoints*3; i++) {
        if(cartesianDataGrid[i] > max){
            max = cartesianDataGrid[i];
        }
    }
    return max;
}

float FlowDataSource::getLowest()
{

}

void FlowDataSource::gen_tornado(int xs, int ys, int zs, int time, float *tornado)
{
    float x, y, z;
    int ix, iy, iz;
    float r, xc, yc, scale, temp, z0;
    float r2 = 8;
    float SMALL = 0.00000000001;
    float xdelta =  1.0 / (xs-1.0);
    float ydelta = 1.0 / (ys-1.0);
    float zdelta =  1.0 / (zs-1.0);
    for( iz = 0; iz < zs; iz++ )
    {
       z = iz * zdelta;                        // map z to 0->1
       xc = 0.5 + 0.1*sin(0.04*time+10.0*z);   // For each z-slice, determine the spiral circle.
       yc = 0.5 + 0.1*cos(0.03*time+3.0*z);    //    (xc,yc) determine the center of the circle.
       r = 0.1 + 0.4 * z*z + 0.1 * z * sin(8.0*z); //  The radius also changes at each z-slice.
       r2 = 0.2 + 0.1*z;                           //    r is the center radius, r2 is for damping
       for( iy = 0; iy < ys; iy++ )
       {
          y = iy * ydelta;
          for( ix = 0; ix < xs; ix++ )
          {
              x = ix * xdelta;
              temp = sqrt( (y-yc)*(y-yc) + (x-xc)*(x-xc) );
              scale = fabs( r - temp );
   /*
    *  I do not like this next line. It produces a discontinuity
    *  in the magnitude. Fix it later.
    *
    */
             if ( scale > r2 )
                scale = 0.8 - scale;
             else
                scale = 1.0;
              z0 = 0.1 * (0.1 - temp*z );
             if ( z0 < 0.0 )  z0 = 0.0;
             temp = sqrt( temp*temp + z0*z0 );
              scale = (r + r2 - temp) * scale / (temp + SMALL);
              scale = scale / (1+z);
              *tornado++ = scale * (y-yc) + 0.1*(x-xc);
              *tornado++ = scale * -(x-xc) + 0.1*(y-yc);
              *tornado++ = scale * z0;
           }
        }
     }
}

FlowDataSource::~FlowDataSource()
{
    cartesianDataGrid = nullptr;
    delete cartesianDataGrid;
}
