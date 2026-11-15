#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
// BYTES: Extreme Speed calls the out-of-line Vec2f assignment.
#define MT_VEC2F_ASSIGN_NOINLINE
#define MT_VEC3F_CTOR_NOINLINE
#define MATH_ATAN2F_NOINLINE // BYTES: atan2f is called as this unit's weak copy
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
#include <so/controller/so_controller_module_impl.h>
#include <so/model/so_model_module_impl.h>
#include <so/turn/so_turn_module.h>
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
    static void turn(soModuleAccesser* moduleAccesser);
    static void set_pose(soModuleAccesser* moduleAccesser);
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
bool check_dir(int touchMask, bool attach, float lr, soModuleAccesser* moduleAccesser);
bool check_attach(float lr, soModuleAccesser* moduleAccesser);
Vec2f get_vector(float angle, float length);
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
    if ((ground.isTouch(static_cast<grCollStatus::TouchMask>(2), 0) && check_attach(1.0f, moduleAccesser)) ||
        (ground.isTouch(static_cast<grCollStatus::TouchMask>(4), 0) && check_attach(-1.0f, moduleAccesser))) {
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

// The map name is Vec2f::dotProduct; the symbol keeps the free-function spelling it has in symbols.txt.
inline float dotProduct(Vec2f* a, Vec2f* b) __attribute__((never_inline));
inline float dotProduct(Vec2f* a, Vec2f* b) {
    return a->m_x * b->m_x + a->m_y * b->m_y;
}

// The wall can be clung to when its slope is between the constants 0xc9d and 0xc9c.
static inline bool isAttachAngle(soModuleAccesser* moduleAccesser, float angle) {
    if (angle >= soValueAccesser::getConstantFloat(moduleAccesser, 0xc9c, 0) ||
        angle <= soValueAccesser::getConstantFloat(moduleAccesser, 0xc9d, 0)) {
        return false;
    }
    return true;
}

// The slope in degrees of the wall touched on the given side (90 for an upright wall).
static inline float getWallSlope(soModuleAccesser* moduleAccesser, float lr) {
    Vec2f normal(0.0f, 1.0f);
    float sign;
    if (lr >= 0.0f) {
        Vec2f::copy(normal, moduleAccesser->getGroundModule().getTouchNormal(2, 0));
        sign = -1.0f;
    } else {
        Vec2f::copy(normal, moduleAccesser->getGroundModule().getTouchNormal(4, 0));
        sign = 1.0f;
    }
    return 90.0f + 57.29578f * (sign * atan2f(normal.m_x, normal.m_y));
}

// The rush ends in a wall cling when the stick is held away from a wall of the right slope on the given side.
bool check_attach(float lr, soModuleAccesser* moduleAccesser) {
    soGroundModule& ground = moduleAccesser->getGroundModule();
    int clingCount = moduleAccesser->getWorkManageModule().getInt(0x1000000b);
    float stickMin = soValueAccesser::getConstantFloat(moduleAccesser, 0xc97, 0);
    float stickX = moduleAccesser->getControllerModule().getStickX();
    if (clingCount <= 0 && static_cast<float>(fabs(stickX)) >= stickMin && stickX * lr < 0.0f) {
        if (isAttachAngle(moduleAccesser, getWallSlope(moduleAccesser, lr))) {
            if (!ground.isTouch(1, 0)) {
                if (lr >= 0.0f) {
                    if (ground.isAttachable(2, 0)) {
                        return true;
                    }
                } else {
                    if (ground.isAttachable(4, 0)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

static inline s16 getAngle16(const Vec2f& direction) {
    return static_cast<s16>(32768.0f * (static_cast<float>(atan2(direction.m_y, direction.m_x)) / 3.1415927f));
}

// A surface met head-on ends the rush (in a wall cling when allowed, else in the bound status 0x11d); a surface met
// at a shallow angle bends the flight along it by at most the constant 0xfbe.
bool check_dir(int touchMask, bool attach, float lr, soModuleAccesser* moduleAccesser) {
    soGroundModule& ground = moduleAccesser->getGroundModule();
    if (ground.isTouch(touchMask, 0)) {
        Vec2f normal = moduleAccesser->getGroundModule().getTouchNormal(touchMask, 0);
        Vec2f speed = moduleAccesser->getKineticModule().getSumSpeed(soKineticEnergy::AttributeFlag(1));
        float angle = normal.angle(&speed);
        bool headOn = angle >= 0.017453292f * (90.0f + soValueAccesser::getConstantFloat(moduleAccesser, 0xfbf, 0));
        if (headOn) {
            if (attach && check_attach(lr, moduleAccesser)) {
                soWorkManageModule& work = moduleAccesser->getWorkManageModule();
                work.onFlag(0x22000014);
                work.setInt(0x68, 0x20000001);
            } else {
                soWorkManageModule& work = moduleAccesser->getWorkManageModule();
                work.onFlag(0x22000014);
                work.setInt(0x11d, 0x20000001);
            }
            return true;
        }
        soKineticEnergyNormal& stop = dynamic_cast<soKineticEnergyNormal&>(*moduleAccesser->getKineticModule().getEnergy(3));
        Vec2f velocity = stop.getSpeed();
        if (velocity.length() > 1.1920929e-7f) {
            Vec2f wall = ground.getTouchNormal(touchMask, 0);
            if (dotProduct(&velocity, &wall) < 0.0f) {
                soWorkManageModule& work = moduleAccesser->getWorkManageModule();
                float turnMax = soValueAccesser::getConstantFloat(moduleAccesser, 0xfbe, 0);
                Vec2f wallDirection = wall;
                s16 difference = getAngle16(velocity) - getAngle16(wallDirection);
                int quarter;
                if (difference < 0) {
                    quarter = difference + 0x4000;
                } else {
                    quarter = difference - 0x4000;
                }
                float delta = 3.1415927f * (static_cast<float>(quarter) / 32768.0f);
                float limit = 0.017453292f * turnMax;
                if (delta >= limit) {
                    delta = -limit;
                } else if (delta <= -limit) {
                    delta = limit;
                } else {
                    delta = -delta;
                }
                float direction = work.getFloat(0x21000005) + delta;
                work.setFloat(direction, 0x21000005);
                Vec2f newSpeed;
                Vec2f::copy(newSpeed, get_vector(direction, velocity.length()));
                stop.m_speed = newSpeed;
            }
        }
    }
    return false;
}

// When a turn ends the flight direction is mirrored and the rush restarts with the speed constant 0xfbd.
void ftLucarioStatusUniqProcessSpecialHiRush::turn(soModuleAccesser* moduleAccesser) {
    soWorkManageModule& work = moduleAccesser->getWorkManageModule();
    soTurnModule& turnModule = *static_cast<soTurnModule*>(moduleAccesser->m_enumerationStart->m_turnModule);
    soKineticModule& kinetic = moduleAccesser->getKineticModule();
    bool turning = turnModule.isTurn();
    bool wasTurning = work.isFlag(0x22000015);
    work.setFlag(turning, 0x22000015);
    if (turning != wasTurning && !turning) {
        float direction = work.getFloat(0x21000005);
        float y = sin(direction);
        float x = cos(direction);
        direction = atan2(y, -x);
        float magnitude = fabs(direction);
        if (magnitude <= 0.05f) {
            direction = 0.0f;
        } else if (static_cast<float>(fabs(3.1415927f - magnitude)) <= 0.05f) {
            direction = 3.1415927f;
        }
        work.setFloat(direction, 0x21000005);
        Vec2f speed;
        Vec2f::copy(speed, get_vector(direction, soValueAccesser::getConstantFloat(moduleAccesser, 0xfbd, 0)));
        kinetic.clearSpeedAll();
        kinetic.unableEnergyAll();
        soKineticEnergyNormal& stop = dynamic_cast<soKineticEnergyNormal&>(*kinetic.getEnergy(3));
        stop.m_speed = speed;
        stop.enable();
        work.setFloat(-work.getFloat(0x21000004), 0x21000004);
        work.setFloat(-work.getFloat(0x21000008), 0x21000008);
        work.setFloat(-work.getFloat(0x21000006), 0x21000006);
    }
}

// Leans the two body nodes 0x12e and 0x12f into the flight direction (work float 0x21000005, radians).
void ftLucarioStatusUniqProcessSpecialHiRush::set_pose(soModuleAccesser* moduleAccesser) {
    float direction = moduleAccesser->getWorkManageModule().getFloat(0x21000005);
    float magnitude = fabs(direction);
    float lean;
    float tilt;
    float lr;
    if (static_cast<float>(fabs(magnitude - 1.5707964f)) > 1.1920929e-7f) {
        if (magnitude < 1.5707964f) {
            lean = 1.5707964f - direction;
            tilt = 1.5707964f + -direction;
            lr = 1.0f;
        } else {
            if (direction > 0.0f) {
                lean = 1.5707964f + -direction;
                tilt = -(direction - 1.5707964f);
            } else {
                lean = -direction - 4.712389f;
                tilt = lean;
            }
            lr = 1.0f;
        }
    } else if (direction > 0.0f) {
        lean = 0.0f;
        tilt = lean;
        lr = 1.0f;
    } else {
        lean = 3.1415927f;
        tilt = lean;
        lr = 1.0f;
    }
    soModelModule& model = moduleAccesser->getModelModule();
    int leanNode = model.getCorrectNodeId(0x12e);
    int tiltNode = model.getCorrectNodeId(0x12f);
    Vec3f leanRot;
    leanRot.m_x = 57.29578f * lean;
    leanRot.m_y = 0.0f;
    leanRot.m_z = 0.0f;
    model.setNodeRotate(leanNode, &leanRot);
    Vec3f tiltRot;
    tiltRot.m_x = 0.0f;
    tiltRot.m_y = 57.29578f * tilt;
    tiltRot.m_z = 0.0f;
    model.setNodeRotate(tiltNode, &tiltRot);
    if (!static_cast<soTurnModule*>(moduleAccesser->m_enumerationStart->m_turnModule)->isTurn() && 0.0f != lr) {
        moduleAccesser->getPostureModule().setLr(lr);
        moduleAccesser->getPostureModule().updateRotYLr();
    }
    turn(moduleAccesser);
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
