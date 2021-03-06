#ifndef JSSCRIPTTHREAD_H
#define JSSCRIPTTHREAD_H
#include "ScriptThreadBase.h"
#include "MetaObject.h"
#include <jsapi.h>
#include <stdexcept>
#include <thread>
#include <condition_variable>

namespace metacpp {
namespace scripting {
namespace js {

class JSScriptEngine;

namespace detail
{

struct ClassInfo
{
    JSRuntime *runtime;
    JSClass class_;
    JS::Heap<JSObject *> classObject, ctorObject;
    const MetaObject *metaObject;

    explicit ClassInfo(JSRuntime *runtime);
    ~ClassInfo();
    static void Trace(JSTracer *trc, void *data);
};

Variant fromValue(JSContext *context, const JS::Value& v);
JS::Value toValue(JSContext *context, Variant v);

} // namespace detail

class JSScriptThread : public ScriptThreadBase
{
public:
    explicit JSScriptThread(const ByteArray& bytecode,
                            JSScriptEngine *engine);
    ~JSScriptThread();

    void setCallFunction(const String& functionName, const VariantArray& args);

    bool running() const override;
    Variant run() override;
    bool abort(unsigned timeout_ms) override;
    bool wait(unsigned timeout_ms) override;

    static JSScriptThread *getRunningInstance(JSContext *cx);
    const detail::ClassInfo *findRegisteredClass(const String& name);
private:
    void onError(const char *message, JSErrorReport *report);
    static void dispatchError(JSContext *ctx, const char *message, JSErrorReport *report);
#if MOZJS_MAJOR_VERSION >= 31
    static bool interruptCallback(JSContext *cx);
#else
    static JSBool operationCallback(JSContext *cx);
#endif

    void registerNativeClasses(JSContext *cx, JS::HandleObject global);
    void unregisterNativeClasses();

    static void nativeObjectFinalize(JSFreeOp* fop, JSObject *obj);
#if MOZJS_MAJOR_VERSION >= 31
    static bool nativeObjectConstruct(JSContext *cx, unsigned argc, JS::Value *vp);
    static bool nativeObjectOwnMethodCall(JSContext *cx, unsigned argc, JS::Value *vp);
    static bool nativeObjectStaticMethodCall(JSContext *cx, unsigned argc, JS::Value *vp);
    static bool nativeObjectDynamicGetter(JSContext* cx, JS::HandleObject obj, JS::HandleId id,
                                          JS::MutableHandleValue vp);

#if MOZJS_MAJOR_VERSION >= 46
    static bool nativeObjectDynamicSetter(JSContext* cx, JS::HandleObject obj, JS::HandleId id,
                   JS::MutableHandleValue vp, JS::ObjectOpResult& result);
#else
    static bool nativeObjectDynamicSetter(JSContext* cx, JS::HandleObject obj, JS::HandleId id,
                                          bool strict, JS::MutableHandleValue vp);
#endif
#else
    static JSBool nativeObjectConstruct(JSContext *cx, unsigned argc, jsval *vp);
    static JSBool nativeObjectOwnMethodCall(JSContext *cx, unsigned argc, jsval *vp);
    static JSBool nativeObjectStaticMethodCall(JSContext *cx, unsigned argc, jsval *vp);

    static JSBool nativeObjectDynamicGetter(JSContext* cx, JS::HandleObject obj, JS::HandleId id,
                                          JS::MutableHandleValue vp);
    static JSBool nativeObjectDynamicSetter(JSContext* cx, JS::HandleObject obj, JS::HandleId id,
                                          JSBool strict, JS::MutableHandleValue vp);
#endif

private:
    ByteArray m_bytecode;
    JSScriptEngine *m_engine;
    JSRuntime *m_runtime;
    String m_functionName;
    VariantArray m_arguments;
    Variant m_result;
    std::mutex m_runMutex;
    std::condition_variable m_finishedVariable;
    std::atomic<bool> m_bRunning;
    std::atomic<bool> m_bTerminating;
    std::exception_ptr m_exception;

    Array<detail::ClassInfo *> m_registeredClasses;
};

} // namespace js
} // namespace scripting
} // namespace metacpp

#endif // JSSCRIPTTHREAD_H
