#include <include/i-factory.hpp>
#include <include/profiler/exception.hpp>
#include <include/profiler/perf/perf-sampling-profiler.hpp>


void PerfSamplingProfiler::run(const QString& pathTo, BaseProfiler& baseProfiler)
{
    try
    {
        auto model      = IFactory::createModel(IFactoryType::perf_sample);
        auto controller = IFactory::createController(IFactoryType::perf_sample, model);
        auto view       = IFactory::createView(IFactoryType::perf_sample, model, controller, baseProfiler);

        controller->process(pathTo); // View instance will emit a signal
    }
    catch (Exception& exception)
    {
        baseProfiler.setResult(QString(exception.what())+ QString::number(exception.code()));
    }
    catch (std::exception& exception)
    {
        baseProfiler.setResult(QString(exception.what()));
    }
    catch (...)
    {
        baseProfiler.setResult(QString("Caught unexpected exception"));
    }
}
