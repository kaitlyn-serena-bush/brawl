#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
// BYTES: Extreme Speed calls the out-of-line Vec2f assignment.
#define MT_VEC2F_ASSIGN_NOINLINE
#define MT_VEC3F_CTOR_NOINLINE
#define MT_VEC2F_COPY_MEMBERWISE // BYTES: Vec2f::copy moves the two floats one by one in this unit (speed_mul_energy)
#include <ft/lucario/ft_lucario.h>
#include <ft/ft_kinetic_energy.h>
#include <so/ground/so_ground_module_impl.h>
#include <so/kinetic/so_kinetic_module_impl.h>
#include <so/situation/so_situation_module_impl.h>
#include <so/so_kinetic_energy_normal.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <so/status/so_status_module_impl.h>
#include <so/work/so_work_manage_module_impl.h>
#include <math.h>
#include <so/so_kinetic_utility.h>
#include <so/posture/so_posture_module_impl.h>
#include <types.h>

class ftLucarioStatusUniqProcessSpecialHi : public soStatusUniqProcess {
public:
    virtual ~ftLucarioStatusUniqProcessSpecialHi() { }
    virtual void initStatus(soModuleAccesser*);
    virtual void execStatus(soModuleAccesser*);
};

class ftLucarioStatusUniqProcessSpecialHiRush : public soStatusUniqProcess {
public:
    virtual ~ftLucarioStatusUniqProcessSpecialHiRush() { }
    virtual void initStatus(soModuleAccesser*);
    virtual void exitStatus(soModuleAccesser*, int);
    virtual void execStatus(soModuleAccesser*);
    virtual void execFixPos(soModuleAccesser*);
};

class ftLucarioStatusUniqProcessSpecialHiRushEnd : public soStatusUniqProcess {
public:
    virtual ~ftLucarioStatusUniqProcessSpecialHiRushEnd() { }
    virtual void initStatus(soModuleAccesser*);
    virtual void exitStatus(soModuleAccesser*, int);
    virtual void execFixPos(soModuleAccesser*);
};

class ftLucarioStatusUniqProcessSpecialHiBound : public soStatusUniqProcess {
public:
    virtual ~ftLucarioStatusUniqProcessSpecialHiBound() { }
    virtual void initStatus(soModuleAccesser*);
    virtual void exitStatus(soModuleAccesser*, int);
};

void set_end_param(soModuleAccesser* moduleAccesser);
// HYPOTHESIS: map name set_end_lr(soModuleAccesser*); kept fn_ until its literal-pool order matches.
extern "C" float fn_118_F1E4(soModuleAccesser* moduleAccesser);
// HYPOTHESIS: the map gives no parameter types; these follow the register use.
extern "C" int fn_118_F6EC(float lr, soModuleAccesser* moduleAccesser);
void set_landing_status(int frame, float rate, soModuleAccesser* moduleAccesser);
void speed_mul(float x, float y, soModuleAccesser* moduleAccesser);
void speed_mul_energy(soKineticModule* kineticModule, int energy, float x, float y);

extern ftLucarioStatusUniqProcessSpecialHiRush g_ftLucarioStatusUniqProcessSpecialHiRush;

// The start of the move: the horizontal speed is divided by the constant 0xfb8, the fall stops.
void ftLucarioStatusUniqProcessSpecialHi::initStatus(soModuleAccesser* moduleAccesser) {
    soWorkManageModule& work = moduleAccesser->getWorkManageModule();
    soKineticModule& kinetic = moduleAccesser->getKineticModule();
    soKineticEnergyNormal& stop = dynamic_cast<soKineticEnergyNormal&>(*kinetic.getEnergy(3));
    Vec2f speed = kinetic.getSumSpeed(soKineticEnergy::AttributeFlag(1));
    speed.m_x /= soValueAccesser::getConstantFloat(moduleAccesser, 0xfb8, 0);
    stop.resetEnergy(6, &Vec2f(speed.m_x, 0.0f), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
    stop.enable();
    ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*kinetic.getEnergy(1));
    gravity.m_speedY = 0.0f;
    gravity.enable();
    ftKineticEnergyDisableAndClear(2, moduleAccesser);
    ftKineticEnergyDisableAndClear(0, moduleAccesser);
    work.setFloat(moduleAccesser->getPostureModule().getLr(), 0x21000004);
    ftLucario::setMachValidity(moduleAccesser, false);
}

// In the air the fall is switched on by the flag 0x22000011 of the animation; the stop energy brakes with 0xfb9.
void ftLucarioStatusUniqProcessSpecialHi::execStatus(soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getSituationModule().getKind() == 2) {
        soWorkManageModule& work = moduleAccesser->getWorkManageModule();
        soKineticModule& kinetic = moduleAccesser->getKineticModule();
        if (work.isFlag(0x22000011)) {
            ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*kinetic.getEnergy(1));
            gravity.m_gravity = -soValueAccesser::getConstantFloat(moduleAccesser, 0xfba, 0);
        } else {
            ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*kinetic.getEnergy(1));
            gravity.m_gravity = 0.0f;
        }
        soKineticEnergyNormal& stop = dynamic_cast<soKineticEnergyNormal&>(*kinetic.getEnergy(3));
        stop.m_brake = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xfb9, 0), 0.0f);
    }
}

void ftLucarioStatusUniqProcessSpecialHiRush::initStatus(soModuleAccesser*) { }
void ftLucarioStatusUniqProcessSpecialHiRush::execStatus(soModuleAccesser*) { }

void ftLucarioStatusUniqProcessSpecialHiRush::exitStatus(soModuleAccesser* moduleAccesser, int) {
    if (moduleAccesser->getSituationModule().getKind() == 2) {
        int frame = soValueAccesser::getConstantInt(moduleAccesser, 0x5dc3, 0);
        set_landing_status(frame, soValueAccesser::getConstantFloat(moduleAccesser, 0xfc3, 0), moduleAccesser);
        set_landing_status(5, 1.0f, moduleAccesser);
    }
}

void ftLucarioStatusUniqProcessSpecialHiRush::execFixPos(soModuleAccesser*) { }

void ftLucarioStatusUniqProcessSpecialHiRushEnd::initStatus(soModuleAccesser* moduleAccesser) {
    fn_118_F1E4(moduleAccesser);
    soKineticEnergyNormal& energy = dynamic_cast<soKineticEnergyNormal&>(*moduleAccesser->getKineticModule().getEnergy(3));
    Vec2f brake;
    brake.m_x = soValueAccesser::getConstantFloat(moduleAccesser, 0xfc1, 0);
    brake.m_y = 0.0f;
    energy.m_brake = brake;
    energy.enable();
}

void ftLucarioStatusUniqProcessSpecialHiRushEnd::execFixPos(soModuleAccesser* moduleAccesser) {
    soGroundModule& ground = moduleAccesser->getGroundModule();
    if ((ground.isTouch(static_cast<grCollStatus::TouchMask>(2), 0) && fn_118_F6EC(1.0f, moduleAccesser)) ||
        (ground.isTouch(static_cast<grCollStatus::TouchMask>(4), 0) && fn_118_F6EC(-1.0f, moduleAccesser))) {
        moduleAccesser->getStatusModule().changeStatusRequest(0x68, moduleAccesser);
    }
}

void ftLucarioStatusUniqProcessSpecialHiRushEnd::exitStatus(soModuleAccesser* moduleAccesser, int) {
    set_end_param(moduleAccesser);
}

void ftLucarioStatusUniqProcessSpecialHiBound::initStatus(soModuleAccesser* moduleAccesser) {
    fn_118_F1E4(moduleAccesser);
    if (moduleAccesser->getSituationModule().getKind() == 0) {
        moduleAccesser->getKineticModule().changeKinetic(6, moduleAccesser);
    } else {
        moduleAccesser->getKineticModule().changeKinetic(0xd, moduleAccesser);
    }
    speed_mul(soValueAccesser::getConstantFloat(moduleAccesser, 0xfc4, 0), 1.0f, moduleAccesser);
    soKineticEnergyNormal& energy = dynamic_cast<soKineticEnergyNormal&>(*moduleAccesser->getKineticModule().getEnergy(3));
    Vec2f brake;
    brake.m_x = soValueAccesser::getConstantFloat(moduleAccesser, 0xfc1, 0);
    brake.m_y = 0.0f;
    energy.m_brake = brake;
    energy.enable();
}

void ftLucarioStatusUniqProcessSpecialHiBound::exitStatus(soModuleAccesser* moduleAccesser, int status) {
    soStatusUniqProcess& rush = g_ftLucarioStatusUniqProcessSpecialHiRush;
    rush.exitStatus(moduleAccesser, status);
    set_end_param(moduleAccesser);
}

void set_end_param(soModuleAccesser* moduleAccesser) {
    soWorkManageModule& work = moduleAccesser->getWorkManageModule();
    work.setFloat(0.0f, 0x11000000);
    work.setFloat(1.0f, 0x11000001);
    work.onFlag(0x12000003);
}

extern "C" float fn_118_F1E4(soModuleAccesser* moduleAccesser) {
    soWorkManageModule& work = moduleAccesser->getWorkManageModule();
    float speed = work.getFloat(0x21000008);
    float lr;
    double wide = fabs(speed);
    float magnitude = wide;
    if (magnitude <= 1.1920929e-7f) {
        lr = work.getFloat(0x21000004);
    } else if (speed > 0.0f) {
        lr = 1.0f;
    } else {
        lr = -1.0f;
    }
    moduleAccesser->getPostureModule().setLr(lr);
    moduleAccesser->getPostureModule().updateRotYLr();
    return lr;
}

void set_landing_status(int frame, float rate, soModuleAccesser* moduleAccesser) {
    moduleAccesser->getWorkManageModule().setFloat(frame, 0x11000000);
    moduleAccesser->getWorkManageModule().setFloat(rate, 0x11000001);
    moduleAccesser->getWorkManageModule().onFlag(0x12000003);
}

void speed_mul(float x, float y, soModuleAccesser* moduleAccesser) {
    soKineticModule& kinetic = moduleAccesser->getKineticModule();
    speed_mul_energy(&kinetic, 3, x, y);
    speed_mul_energy(&kinetic, 2, x, y);
    speed_mul_energy(&kinetic, 0, x, y);
    speed_mul_energy(&kinetic, 1, x, y);
}

// Scales the speed of one kinetic energy (the gravity energy only has a vertical speed).
void speed_mul_energy(soKineticModule* kineticModule, int energy, float x, float y) {
    switch (energy) {
    case 1: {
        ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*kineticModule->getEnergy(energy));
        Vec2f speed;
        Vec2f::copy(speed, gravity.getSpeed());
        gravity.m_speedY = speed.m_y * y;
        break;
    }
    default: {
        soKineticEnergyNormal& normal = dynamic_cast<soKineticEnergyNormal&>(*kineticModule->getEnergy(energy));
        Vec2f speed;
        Vec2f::copy(speed, normal.getSpeed());
        speed.m_x *= x;
        speed.m_y *= y;
        normal.m_speed = speed;
        break;
    }
    }
}

Vec2f get_vector(float angle, float length) {
    Vec2f dir;
    dir.m_x = cos(angle);
    dir.m_y = sin(angle);
    double wide = fabs(dir.m_y);
    float magnitude = wide;
    if (magnitude <= 0.01f) {
        dir.m_y = 0.0f;
    }
    Vec2f vector;
    vector.m_x = dir.m_x * length;
    vector.m_y = dir.m_y * length;
    return vector;
}

ftLucarioStatusUniqProcessSpecialHi g_ftLucarioStatusUniqProcessSpecialHi;
ftLucarioStatusUniqProcessSpecialHiRush g_ftLucarioStatusUniqProcessSpecialHiRush;
ftLucarioStatusUniqProcessSpecialHiRushEnd g_ftLucarioStatusUniqProcessSpecialHiRushEnd;
ftLucarioStatusUniqProcessSpecialHiBound g_ftLucarioStatusUniqProcessSpecialHiBound;
