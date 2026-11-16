#define FT_POOL_ROOT_NONPOLYMORPHIC
#define SO_GENERAL_WORK_BOUNDED_CLEAR
#define SO_INSTANCE_MANAGER_FULL_PROPERTY_DTOR_OUT_OF_LINE
#define FT_SOUND_GENERATOR_DTOR_NOINLINE
#define SO_ARRAY_SPLIT_VECTOR_CTOR
#define FT_KOOPA_ARTICLE_POOLS
#define WN_ARTICLE_MANAGE_BUILDER_OUT_OF_LINE
#define FT_PARAM_ACCESSER_TYPED_DTOR
#define FT_TEAM_TYPED_INTERFACE
#define WN_KINETIC_MEDIATOR_INLINE_DTOR
#define FT_MODULE_ACCESSER_BUILDER_BASE_BUILD_DATA // the builder takes the base build data: its slope limit literal (20.0) stays in the pool
#include <ft/builder/ft_dol_array_list.h>
// The 291-entry process vector is a whole class of sora_melee (the anim cmd one is declared in the list header).
FT_DOL_ARRAY_VECTOR(soStatusUniqProcess*, 291);
#include <ft/ft_class_info_impl.h>
#include <ft/koopa/ft_koopa.h>
#include <ft/koopa/ft_koopa_extend_param_accesser.h>
#include <ft/koopa/ft_koopa_transactor.h>
#include <so/article/so_article_mediator.h>
#include <so/so_value_accesser.h>

// The articles' sound builder teardown inlines this empty destructor (same form as ft_pit.cpp and ft_snake.cpp).
inline soSound3dGeneratorAccesserImpl::~soSound3dGeneratorAccesserImpl() { }

#undef WN_ARTICLE_NATIVE_BUILDERS
#define FT_BC ftKoopaBuildConfig
#include <ft/builder/ft_builder_noinline.h>

void ftKoopa::change(void* work, int startKind) {
    onStart(startKind);
    Fighter::changeSucceedCore(work, 0x122);
}

#include <so/so_slow.h>

template <class T> T (CLAMP)(T value, T minimum, T maximum);

void ftKoopa::processUpdate() {
    Fighter::processUpdate();
    if (soSlow::getInstance()->isEstimate() == true && !m_moduleAccesser->getStopModule().isStop()) {
        float first = m_moduleAccesser->getWorkManageModule().getFloat(0x11000014);
        float second = m_moduleAccesser->getWorkManageModule().getFloat(0x11000013);
        if (m_moduleAccesser->getStatusModule().getStatusKind() != 0x112) {
            first += soValueAccesser::getConstantFloat(m_moduleAccesser, 0xfaa, 0);
            second += soValueAccesser::getConstantFloat(m_moduleAccesser, 0xfab, 0);
        } else if (m_moduleAccesser->getWorkManageModule().getInt(0x20000002) == 1) {
            first -= soValueAccesser::getConstantFloat(m_moduleAccesser, 0xfac, 0);
            second -= soValueAccesser::getConstantFloat(m_moduleAccesser, 0xfad, 0);
        }
        float firstMinimum = soValueAccesser::getConstantFloat(m_moduleAccesser, 0xfa7, 0);
        float firstMaximum = soValueAccesser::getConstantFloat(m_moduleAccesser, 0xfa6, 0);
        first = CLAMP<float>(first, firstMinimum, firstMaximum);
        m_moduleAccesser->getWorkManageModule().setFloat(first, 0x11000014);
        float secondMinimum = soValueAccesser::getConstantFloat(m_moduleAccesser, 0xfa9, 0);
        float secondMaximum = soValueAccesser::getConstantFloat(m_moduleAccesser, 0xfa8, 0);
        second = CLAMP<float>(second, secondMinimum, secondMaximum);
        m_moduleAccesser->getWorkManageModule().setFloat(second, 0x11000013);
    }
}

// Status teardown destroys its owned change-request queue before observers.
#pragma dont_inline on
#ifndef FT_REL_LINK_EXTERN // with FT_REL_LINK_EXTERN the queue destructor is the sora_melee function (ft_dol_instances.h)
template soArrayVector<s32, 8>::~soArrayVector();
#endif
#pragma dont_inline off
soStatusModuleImpl::~soStatusModuleImpl() { }

// HYPOTHESIS: unnamed status process instances (not yet named in symbols.txt).
extern "C" {
extern soStatusUniqProcess lbl_27_bss_7D74;
extern soStatusUniqProcess lbl_102_bss_22C;
extern soStatusUniqProcess lbl_102_bss_23C;
extern soStatusUniqProcess lbl_102_bss_25C;
extern soStatusUniqProcess lbl_102_bss_24C;
extern soStatusUniqProcess lbl_102_bss_26C;
extern soStatusUniqProcess lbl_102_bss_27C;
extern soStatusUniqProcess lbl_102_bss_28C;
extern soStatusUniqProcess lbl_102_bss_29C;
extern soStatusUniqProcess lbl_102_bss_2AC;
}

ftKoopaExtendParamAccesser g_ftKoopaExtendParamAccesser;

ftClassInfoImpl<Fighter_Koopa, ftKoopa> g_ftClassInfoKoopa;

ftKoopa::ftKoopa(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftKoopaBuildConfig>(entryId,
                                         Fighter_Koopa,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap),
    m_data(g_ftCommonDataAccesser.getData(Fighter_Koopa)) {
    // Register the status processes in action order.
    soStatusUniqProcess* processes[17] = {0};
    processes[0] = &lbl_27_bss_7D74;
    processes[5] = &lbl_102_bss_22C;
    processes[6] = &lbl_102_bss_23C;
    processes[7] = &lbl_102_bss_25C;
    processes[8] = &lbl_102_bss_24C;
    processes[10] = &lbl_102_bss_26C;
    processes[11] = &lbl_102_bss_26C;
    processes[12] = &lbl_102_bss_27C;
    processes[13] = &lbl_102_bss_28C;
    processes[14] = &lbl_102_bss_29C;
    processes[15] = &lbl_102_bss_2AC;
    m_moduleAccesser->getStatusModule().addRangeUniqProc(processes, 17);
}

// ---- the fighter overrides ------------------------------------------------------------------------------------------
// HYPOTHESIS: the works 0x10000040 / 0x11000013 / 0x11000014 hold the state of the breath (its charge and two parameters of
// the fighter), reset on every start together with the pending-change flags 0x1200003d / 0x1200003e.
void ftKoopa::onStart(int startKind) {
    m_moduleAccesser->getWorkManageModule().setInt(-1, 0x10000040);
    float first = soValueAccesser::getConstantFloat(m_moduleAccesser, 0xfa6, 0);
    m_moduleAccesser->getWorkManageModule().setFloat(first, 0x11000014);
    float second = soValueAccesser::getConstantFloat(m_moduleAccesser, 0xfa8, 0);
    m_moduleAccesser->getWorkManageModule().setFloat(second, 0x11000013);
    m_moduleAccesser->getWorkManageModule().offFlag(0x1200003d);
    m_moduleAccesser->getWorkManageModule().offFlag(0x1200003e);
    Fighter::onStart(startKind);
}

// The breath starts through the transactor of the fighter.
// BYTES: the native function addresses the local static's guard, object and destructor registration separately
// instead of from one pooled BSS base. The setting is per function: unit-wide it breaks the pooled constructor and
// __sinit, and an in-class inline definition makes the static weak and moves it to the end of .bss.
#pragma pool_data off
bool ftKoopa::activeArticle(wnKoopaBreath* weapon, soModuleAccesser* acc) {
    static ftKoopaTransactor instance;
    return instance.activeArticle(weapon, acc);
}
#pragma pool_data reset

// ---- the article holders --------------------------------------------------------------------------------------------
#include <ft/builder/ft_builder_article.h>

struct ftKoopaArticleKind : wnArticleKindInfo {
    ftKind getSubKind() const { return static_cast<ftKind>(subKind); }
    ftKoopaArticleKind() {
        kind = 0;
        subKind = Fighter_Koopa;
    }
};

// The data block of the breath comes from the common data accessor of sora_melee (only declared here).
extern "C" void* fn_27_1496F0(const ftCommonDataAccesser* accesser, s32 subKind, bool* resourceGroup);

FT_DEFINE_ARTICLE_HOLDER(, wnKoopaBreath, wnKoopaBreathData, 0, ftKoopaArticleKind, fn_27_1496F0)

// ---- the articles and their mediator --------------------------------------------------------------------------------

// The native ownership chain calls these destructors out of line.
#pragma dont_inline on
template <class W>
wnArticleHolder<W>::~wnArticleHolder() { }
template <class W, int N>
wnArticleSubPool<W, N>::~wnArticleSubPool() { }
template wnArticleHolder<wnKoopaBreath>::~wnArticleHolder();
template <class Mediator>
wnSelectedArticleMediator<Mediator>::~wnSelectedArticleMediator() { }
template <class Mediator, int N>
wnArticleManageModuleBuilder<Mediator, N>::~wnArticleManageModuleBuilder() { }
template <class Mediator, int N>
wnArticleManageModuleBuilder<Mediator, N>::wnArticleManageModuleBuilder(soModuleAccesser* acc) :
    m_articles(0), m_observers(N, 0), m_mediator(acc), m_module(acc, &m_articles, m_mediator.getMediator(), &m_observers) { }
template wnSelectedArticleMediator<ftKoopaArticleMediator>::~wnSelectedArticleMediator();
template wnArticleManageModuleBuilder<ftKoopaArticleMediator, 5>::~wnArticleManageModuleBuilder();
template wnArticleManageModuleBuilder<ftKoopaArticleMediator, 5>::wnArticleManageModuleBuilder(soModuleAccesser*);
ftKoopaArticleMediator::~ftKoopaArticleMediator() { }
#pragma dont_inline off

s32 ftKoopaArticleMediator::getMediateNum() { return 1; }
void ftKoopaArticleMediator::setAutoRecycle(bool enabled) { m_autoRecycle = enabled; }

// ---- the article mediator -------------------------------------------------------------------------------------------
// Slots: 0 Breath (the rest are unused).

#define FT_KOOPA_POOL_BREATH_BASE static_cast<wnArticlePool<wnKoopaBreath, 6, soInstancePoolRoot>&>(m_pools)
#define FT_KOOPA_POOL_BREATH FT_KOOPA_POOL_BREATH_BASE.getSub()

#define FT_KOOPA_UNUSED_SLOTS(value) \
    WN_ARTICLE_UNUSED_SLOT(1, value) WN_ARTICLE_UNUSED_SLOT(2, value) WN_ARTICLE_UNUSED_SLOT(3, value) \
    WN_ARTICLE_UNUSED_SLOT(4, value) WN_ARTICLE_UNUSED_SLOT(5, value) WN_ARTICLE_UNUSED_SLOT(6, value) \
    WN_ARTICLE_UNUSED_SLOT(7, value) WN_ARTICLE_UNUSED_SLOT(8, value) WN_ARTICLE_UNUSED_SLOT(9, value) \
    WN_ARTICLE_UNUSED_SLOT(10, value) WN_ARTICLE_UNUSED_SLOT(11, value) WN_ARTICLE_UNUSED_SLOT(12, value) \
    WN_ARTICLE_UNUSED_SLOT(13, value) WN_ARTICLE_UNUSED_SLOT(14, value) WN_ARTICLE_UNUSED_SLOT(15, value) \
    WN_ARTICLE_UNUSED_SLOT(16, value)

void ftKoopaArticleMediator::deactivate() {
    for (s32 i = 0; i < 6; ++i) {
        wnKoopaBreath* weapon = FT_KOOPA_POOL_BREATH.getInstanceAt(i);
        if (!static_cast<soArticle&>(*weapon).setDeactivateDescendant()) {
            return;
        }
    }
}

s32 ftKoopaArticleMediator::getGenerateMaxNum(s32 articleId) {
    switch (articleId) {
    case 0: return wnArticleSlotGenerateMaxNum(6, WN_ARTICLE_SLOT_TAGS);
    FT_KOOPA_UNUSED_SLOTS(0)
    default: return 0;
    }
}

// The counter is a plain aggregate here; the original counts with a functor whose methods MWCC inlines.
struct ftKoopaActiveCounter {
    bool (*m_isActive)(soArticle*);
    s32 m_activeNum;
    s32 m_inactiveNum;
};

s32 ftKoopaArticleMediator::getActiveNum(soModuleAccesser*, s32 articleId) {
    switch (articleId) {
    case 0: return wnArticleSlotActiveNum<wnArticlePool<wnKoopaBreath, 6, soInstancePoolRoot>, ftKoopaActiveCounter>(this, WN_ARTICLE_SLOT_TAGS);
    FT_KOOPA_UNUSED_SLOTS(0)
    default: return 0;
    }
}

bool ftKoopaArticleMediator::isGeneratable(soModuleAccesser*, s32 articleId) {
    switch (articleId) {
    case 0: return wnArticleSlotIsGeneratable<wnArticlePool<wnKoopaBreath, 6, soInstancePoolRoot> >(this, WN_ARTICLE_SLOT_TAGS);
    FT_KOOPA_UNUSED_SLOTS(false)
    default: return false;
    }
}

template <class W> struct ftKoopaArticleActivator;
template <> struct ftKoopaArticleActivator<wnKoopaBreath> {
    static bool activate(wnKoopaBreath* weapon, soModuleAccesser* acc) { return ftKoopa::activeArticle(weapon, acc); }
};

soArticle* ftKoopaArticleMediator::generate(s32 articleId, soModuleAccesser* acc) {
    switch (articleId) {
    case 0: return wnArticleSlotGenerate<ftKoopaArticleActivator<wnKoopaBreath> >(static_cast<wnArticlePool<wnKoopaBreath, 6, soInstancePoolRoot>&>(m_pools), acc, WN_ARTICLE_SLOT_TAGS);
    FT_KOOPA_UNUSED_SLOTS(wnGetNullArticle())
    default: return wnGetNullArticle();
    }
}

bool ftKoopaArticleMediator::shoot(soModuleAccesser* acc, soArticle* article) {
    switch (article->getArticleId()) {
    case 0: return wnArticleSlotShoot<wnKoopaBreath>(article, WN_ARTICLE_SLOT_TAGS);
    FT_KOOPA_UNUSED_SLOTS(true)
    default: return false;
    }
}
