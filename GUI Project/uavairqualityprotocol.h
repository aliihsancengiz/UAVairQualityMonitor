#ifndef UAVAIRQUALITYPROTOCOL_H
#define UAVAIRQUALITYPROTOCOL_H


#include "pb/pb_encode.h"
#include "pb/pb_decode.h"
#include "UAVairQuality.pb.h"

#include <QDebug>

struct Event_t
{
    uint32_t SO2,NO2,CO,CO2;
};


class UAVairQualityProtocol
{
    public:
        Event_t parseFrame(char *rxBuffer)
        {
            Event_t temp;
            mRxStream=pb_istream_from_buffer((uint8_t*)rxBuffer,100);
            pb_decode(&mRxStream,AirQualityMessageFrame_fields,&mRxMessage);
            temp.SO2=mRxMessage.SO2_RawData;
            temp.NO2=mRxMessage.NO2_RawData;
            temp.CO=mRxMessage.CO_RawData;
            temp.CO2=mRxMessage.CO2_RawDate;
            return temp;
        }
    private:
        AirQualityMessageFrame mRxMessage=AirQualityMessageFrame_init_zero;
        pb_istream_t mRxStream;
};

#endif // UAVAIRQUALITYPROTOCOL_H
