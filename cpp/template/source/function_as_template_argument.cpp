#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

// ------------------------------------------------------------------------------
struct Area
{
  std::uint16_t width;
  std::uint16_t height;
};

using AreaVector = std::vector<Area>;

std::ostream& operator<<(std::ostream& ostream, const Area& area)
{
  if (!ostream)
  {
    return ostream;
  }

  ostream
    << "Area["
    << "width=" << area.width
    << " height=" << area.height
    << "]";
  return ostream;
}

// ------------------------------------------------------------------------------
// function as template argument
//
// Related discussion:
// std::function vs template: https://stackoverflow.com/questions/14677997/stdfunction-vs-template


template <typename AreaSizeFunction>
AreaVector::iterator sortAndFindBiggestArea(const AreaVector::iterator& rangeBegin,
                                            const AreaVector::iterator& rangeEnd,
                                            AreaSizeFunction getAreaSize)
{
  const auto biggestFirst = [getAreaSize](const Area& area1,
                                          const Area& area2)
                            {
                              return getAreaSize(area1) > getAreaSize(area2);
                            };
  std::sort(rangeBegin, rangeEnd, biggestFirst);
  return std::equal_range(rangeBegin, rangeEnd, *rangeBegin, biggestFirst).second;
}

// ------------------------------------------------------------------------------
std::uint32_t getAreaSize(const Area& area)
{
  return area.width * area.height;
}


//==============================================================================
#include <gtest/gtest.h>

namespace
{
  const AreaVector kAreaVector = { {1, 1},
                                   {1, 5},
                                   {1, 10},
                                   {5, 1},
                                   {5, 5},
                                   {5, 10},
                                   {10, 1},
                                   {10, 5},
                                   {10, 10} };
}

TEST(FunctionAsTemplateArgumentTest, sortAndFindBiggestArea)
{
  AreaVector areaVector = kAreaVector;
  const auto rangeEnd = sortAndFindBiggestArea(areaVector.begin(), areaVector.end(), getAreaSize);
  for (auto it = areaVector.begin(); it != rangeEnd; ++it)
  {
    EXPECT_EQ(getAreaSize(*areaVector.begin()), getAreaSize(*it));
  }
  for (auto it = rangeEnd; it != areaVector.end(); ++it)
  {
    EXPECT_GT(getAreaSize(*areaVector.begin()), getAreaSize(*it));
  }
}
