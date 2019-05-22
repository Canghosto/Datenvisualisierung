#ifndef FLOWDATASOURCE_H
#define FLOWDATASOURCE_H
class FlowDataSource
{
public:
    FlowDataSource();
    void createData();
    float getDataValue(int iz, int iy, int ix, int ic);
    void printValuesOfHorizontalSlice(int iz);
    void printInTriples();
    void gen_tornado( int xs, int ys, int zs, int time, float *tornado );
    ~FlowDataSource();

private:
    float* cartesianDataGrid;
    int dataGridPoints{16};
};
#endif // FLOWDATASOURCE_H
