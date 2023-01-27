#include <gtest/gtest.h>

#include <YAWN/YAWN.hpp>

using namespace YAWN;

TEST(YAWN, Managed) {
    Managed<Reference> managed = new Reference();

    ASSERT_EQ(managed->UseCount(), 1);

    Managed<Reference> copy = managed;

    ASSERT_EQ(managed->UseCount(), 2);

    managed = nullptr;

    ASSERT_FALSE(managed);
    ASSERT_EQ(copy->UseCount(), 1);

    Managed<Reference> copy2 = copy;

    ASSERT_EQ(copy->UseCount(), 2);
    ASSERT_EQ(copy2->UseCount(), 2);
    ASSERT_EQ(copy2.Get(), copy.Get());

    Managed<Reference> moved = Move(copy);

    ASSERT_FALSE(copy);
    ASSERT_TRUE(moved);
    ASSERT_EQ(moved->UseCount(), 2);
    ASSERT_EQ(copy2->UseCount(), 2);
    ASSERT_EQ(copy2.Get(), moved.Get());
}

int Main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
