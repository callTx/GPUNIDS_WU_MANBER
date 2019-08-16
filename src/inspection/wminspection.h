
#ifndef WMINSPECTION_H
#define WMINSPECTION_H

#include <memory>
#include <iostream>
#include "../util/Packet.h"
#include "../ThreadPool/Mutex.h"
#include "inspection.h"

class WMInspection : public Inspection
{
    private:
        Mutex m_inspection_mutex_;
        statistics_t *stats_;
    public:
        WMInspection();
        WMInspection(const WMInspection &) = delete;
        WMInspection& operator = (const WMInspection &) = delete;
        ~WMInspection();

        virtual void wmexec(std::shared_ptr<Packet> pkt,std::string rules) = 0;
        void lock();
        void unlock();
        statistics_t* getStats();
};

