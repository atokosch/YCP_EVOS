/**  A one line description of the class.
 *
 * #include "Orion.hpp"
 * Created 10-24-17  By: Smitty
 *
 * A longer description.
 */

#ifndef ORION_HPP
#define ORION_HPP

#include "../BaseModel/BaseModel.hpp"
#include "../Constants/RegistersOrion.hpp"

class Orion : public BaseModel
{
public:
    Orion(void);
    ~Orion(void);

    void update(void);

    float getVoltageTotal(void);
    float getVoltageAverage(void);
    float getVoltageVariance(void);
    float getVoltageMin(void);
    float getVoltageMax(void);
    
    float getAmperageTotal(void);

    int getVoltageMinCell(void);
    int getVoltageMaxCell(void);

    float getTemperature(void);
};


#endif  //ORION_HPP
