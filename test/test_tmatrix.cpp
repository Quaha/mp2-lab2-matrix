#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5, 0);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> m1(5);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            m1[i][j] = i + j;
        }
    }
    TDynamicMatrix<int> m2(m1);

    EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m1(5);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            m1[i][j] = i + j;
        }
    }
    TDynamicMatrix<int> m2(m1);
    m2[2][2] = 100;

    EXPECT_NE(m1[2][2], m2[2][2]);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(5, 0);

    ASSERT_NO_THROW(m.size());
    EXPECT_EQ(5, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(5, 0);
    m[2][3] = 42;

    EXPECT_EQ(m[2][3], 42);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(5, 0);

    ASSERT_ANY_THROW(m.at(-1, -1) = 6);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(5, 0);

    ASSERT_ANY_THROW(m.at(5, 5) = 5);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(5, 0);

    ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m1(5, 0), m2(5, 0);

    ASSERT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m1(5, 0), m2(10, 0);
    m1 = m2;

    EXPECT_EQ(m1.size(), m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m1(5, 0), m2(10, 0);

    ASSERT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(5, 0);

    EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m1(5, 0), m2(10, 0);

    EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(5, 0), m2(5, 0);

    ASSERT_NO_THROW(m1 + m2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m1(5, 0), m2(10, 0);

    ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(5, 0), m2(5, 0);

    ASSERT_NO_THROW(m1 - m2);
}

TEST(TDynamicMatrix, cant_subtract_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m1(5, 0), m2(10, 0);
    ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(5), m2(5);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m1[i][j] = i + j;
			m2[i][j] = i + j;
		}
	}

	EXPECT_EQ(m1 == m2, true);
}

TEST(TDynamicMatrix, compare_non_equal_matrices_return_false)
{
	TDynamicMatrix<int> m1(5), m2(5);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m1[i][j] = i + j;
			m2[i][j] = i * j;
		}
	}

	EXPECT_EQ(m1 == m2, false);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1; m[0][1] = 2;
	m[1][0] = 3; m[1][1] = 4;

	TDynamicMatrix<int> expected(2);
	expected[0][0] = 2; expected[0][1] = 4;
	expected[1][0] = 6; expected[1][1] = 8;

	EXPECT_EQ(m * 2, expected);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    TDynamicVector<int> v(2);
    v[0] = 1; v[1] = 2;

    TDynamicVector<int> result = m * v;

    EXPECT_EQ(result[0], 5);
    EXPECT_EQ(result[1], 11);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    m2[0][0] = 2; m2[0][1] = 0;
    m2[1][0] = 1; m2[1][1] = 2;

    TDynamicMatrix<int> result = m1 * m2;

    EXPECT_EQ(result[0][0], 4);
    EXPECT_EQ(result[0][1], 4);
    EXPECT_EQ(result[1][0], 10);
    EXPECT_EQ(result[1][1], 8);
}

TEST(TDynamicMatrix, matrices_are_equal_after_multiplication_by_one)
{
    TDynamicMatrix<int> m1(3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m1[i][j] = i + j;
        }
    }

    TDynamicMatrix<int> m2 = m1 * 1;

    EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, multiplying_matrix_by_zero_results_in_zero_matrix)
{
    TDynamicMatrix<int> m1(3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m1[i][j] = i + j;
        }
    }

    TDynamicMatrix<int> m2 = m1 * 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_EQ(m2[i][j], 0);
        }
    }
}

TEST(TDynamicMatrix, can_multiply_matrix_by_identity_matrix)
{
    TDynamicMatrix<int> m(3);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
    m[1][0] = 4; m[1][1] = 5; m[1][2] = 6;
    m[2][0] = 7; m[2][1] = 8; m[2][2] = 9;

    TDynamicMatrix<int> identity(3);
    identity[0][0] = 1; identity[0][1] = 0; identity[0][2] = 0;
    identity[1][0] = 0; identity[1][1] = 1; identity[1][2] = 0;
    identity[2][0] = 0; identity[2][1] = 0; identity[2][2] = 1;

    TDynamicMatrix<int> result = m * identity;

    EXPECT_EQ(result, m);
}

TEST(TDynamicMatrix, can_add_zero_matrix)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    TDynamicMatrix<int> zero(2, 0);

    TDynamicMatrix<int> result = m + zero;

    EXPECT_EQ(result, m);
}

TEST(TDynamicMatrix, zero_matrix_is_not_equal_to_non_zero_matrix)
{
    TDynamicMatrix<int> zero(3);

    TDynamicMatrix<int> m(3);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
    m[1][0] = 4; m[1][1] = 5; m[1][2] = 6;
    m[2][0] = 7; m[2][1] = 8; m[2][2] = 9;

    EXPECT_FALSE(zero == m);
}


