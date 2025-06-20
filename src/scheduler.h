#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <queue>
#include <string>
#include <memory>
#include <vector>
#include "process.h"

// Abstract base class for all scheduling algorithms
class Scheduler {
protected:
    // Statistics
    int totalTime;
    int cpuBusyTime;
    int contextSwitchTime;
    int contextSwitchCount;
    bool isCpuBusy;
    double cpuUtilization;
    std::shared_ptr<Process> currentProcess;
    
    // Process collection
    std::vector<std::shared_ptr<Process>> allProcesses;
    
    // Algorithm name
    std::string name;
    
public:
    Scheduler(const std::string& schedulerName, int switchTime);
    virtual ~Scheduler() = default;
    
    // Pure virtual methods to be implemented by derived classes
    virtual void addProcess(std::shared_ptr<Process> process) = 0;
    virtual std::shared_ptr<Process> getNextProcess() = 0;
    virtual bool shouldPreempt(std::shared_ptr<Process> newProcess) = 0;
    virtual bool isPreemptive() const = 0;
    virtual void updateWaitingTime(int timeElapsed) = 0;
    
    // Common methods
    void setCurrentProcess(std::shared_ptr<Process> process);
    std::shared_ptr<Process> getCurrentProcess() const;
    bool hasCpuProcess() const;
    void clearCurrentProcess();
    
    // Statistics getters and setters
    int getTotalTime() const { return totalTime; }
    int getCpuBusyTime() const { return cpuBusyTime; }
    double getCpuUtilization() const { return cpuUtilization; }
    void setCpuUtilization(double util) { cpuUtilization = util; }
    int getContextSwitchCount() const { return contextSwitchCount; }
    int getContextSwitchTime() const { return contextSwitchTime; }
    const std::string& getName() const { return name; }
    
    // Process collection methods
    void addToAllProcesses(std::shared_ptr<Process> process);
    const std::vector<std::shared_ptr<Process>>& getAllProcesses() const { return allProcesses; }
    
    // Simulation progress
    void setTotalTime(int time) { totalTime = time; }
    void incrementCpuBusyTime(int time) { cpuBusyTime += time; }
    void incrementContextSwitchCount() { contextSwitchCount++; }
};

#endif // SCHEDULER_H
