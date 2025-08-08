#include "../Unity/unity.h"
#include "../binary_trees.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_is_root(void){
    binary_tree_t *root;
    int ret;

    root = binary_tree_node(NULL, 98);
    root->left = binary_tree_node(root, 12);
    root->right = binary_tree_node(root, 402);
    binary_tree_insert_right(root->left, 54);
    binary_tree_insert_right(root, 128);

	ret = binary_tree_is_root(root);
	TEST_ASSERT_TRUE(ret);
	ret = binary_tree_is_root(root->right);
	TEST_ASSERT_FALSE(ret);
	ret = binary_tree_is_root(root->right->right);
	TEST_ASSERT_FALSE(ret);
}

void test_is_root_null(void){
	TEST_ASSERT_EQUAL_INT(0, binary_tree_is_root(NULL));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_is_root);
	RUN_TEST(test_is_root_null);
    return UNITY_END();
}
