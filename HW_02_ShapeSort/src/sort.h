#ifndef SORT_H
#define SORT_H
template <class RandomAccessIterator, class Compare>
void quickSort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
  size_t numElements = std::distance(first, last);
  // already sorted ?
  if (numElements <= 1)
    return;
  RandomAccessIterator pivot = last;
  --pivot;
  // choose middle element as pivot (good choice for partially sorted data)
  if (numElements > 2){
    RandomAccessIterator middle = first;
    std::advance(middle, numElements/2);
    std::iter_swap(middle, pivot);
  }
  // scan beginning from left and right end and swap misplaced elements
  RandomAccessIterator left  = first;
  RandomAccessIterator right = pivot;
  while (left != right){
    // look for mismatches
    while (!comp(*pivot, *left)  && left != right)
      ++left;
    while (!comp(*right, *pivot) && left != right)
      --right;
    // swap two values which are both on the wrong side of the pivot element
    if (left != right)
      std::iter_swap(left, right);
  }
  // move pivot to its final position
  if (pivot != left && comp(*pivot, *left))
    std::iter_swap(pivot, left);
  // subdivide
  quickSort(first,  left, comp);
  quickSort(++left, last, comp); // *left itself is already sorted
}
bool areaAscendingCompare(Shape *a, Shape *b) { return a->area() < b->area(); };
bool areaDescendingCompare(Shape *a, Shape *b) { return a->area() > b->area(); };
bool perimeterAscendingCompare(Shape *a, Shape *b) { return a->perimeter() < b->perimeter(); };
bool perimeterDescendingCompare(Shape *a, Shape *b) { return a->perimeter() > b->perimeter(); };

class AscendingCompare{
  public:
    AscendingCompare(std::string Asc): _Asc(Asc){}
    bool operator()(Shape *a,Shape *b){
      if(_Asc == "area"){
        return a->area() < b->area();
      }else if(_Asc == "perimeter"){
        return a->perimeter() < b->perimeter();
      }else{
        throw std::string("ASCError");
        return false;
      }
    }
  private:
    std::string _Asc;
};

class DescendingCompare{
public:
  DescendingCompare(std::string Des): _Des(Des){}
  bool operator()(Shape *a,Shape *b){
    if(_Des == "area"){
      return a->area() > b->area();
    }else if(_Des == "perimeter"){
      return a->perimeter() > b->perimeter();
    }else{
      throw std::string("DESError");
      return false;
    }
  }
private:
  std::string _Des;
};

#endif
