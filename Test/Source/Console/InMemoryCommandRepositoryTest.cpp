#include <gmock/gmock.h>

#include <memory>

#include "Commands/InMemoryCommandRepository.hpp"
#include "Context.hpp"

namespace Console::Test {
class InMemoryCommandRepositoryTest : public ::testing::Test {
public:
    InMemoryCommandRepositoryTest() noexcept = default;
    virtual ~InMemoryCommandRepositoryTest() noexcept override = default;

protected:
    Context context {};
    InMemoryCommandRepository commandRepository {context};
};
}