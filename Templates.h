#pragma once

template <typename T> T greaterThan(T value1, T value2)
{
	return (value1 > value2);
}

template <typename T> T lessThan(T value1, T value2)
{
	return (value1 < value2);
}

template <typename T> T equalTo(T value1, T value2)
{
	return (value1 == value2);
}

template <typename T> T notEqualTo(T value1, T value2)
{
	return (value1 != value2);
}

