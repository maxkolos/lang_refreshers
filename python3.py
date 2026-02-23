def lists():
  r = [1, 2, 3]
  r.append(4)
  r.insert(0, 0)
  r.extend([5, 6])
  r.reverse()
  assert r.index(5) == 1
  assert 3 in r
  assert r.count(0) == 1
  head, *rest, tail = [1, 2, 3, 4, 5]  # 1, [2, 3, 4], 5
  assert list(range(4)) == [0, 1, 2, 3]
  assert list(range(10)[0:8:2]) == [0, 2, 4, 6]
  assert list(range(2, 7)[0:-3]) == [2, 3]
  assert list(reversed(range(3))) == [2, 1, 0]
lists()

def tuples():
  empty_tuple = ()
  singular_tuple = (1,)
  tuple = (1, 2, 3)
  # API is similar to lists
tuples()

def strings():
  assert len("abc") == 3
  assert "a" in "abc"
  assert "abc"[1] == "b" and "abc"[-1] == "c"
  assert "abcde"[1:-1] == "bcd"
  assert "abc"[::-1] == "cba"
  assert "abcde".find("bc") == 1
  assert "abcde".replace("cd", "123") == "ab123e"
  assert "abcde".startswith("abc") and "abcde".endswith("cde")
  assert "a".upper() == "A" and "B".lower() == "b" and "1".isdigit() and "a".isalpha()
  assert "a, b, c, d".split(", ") == ['a', 'b', 'c', 'd']
  assert "--".join(['a', 'b', 'c']) == "a--b--c"
strings()

def dictionaries():
  d = {"name" : "Alice", "age" : 21}
  assert d == dict(name='Alice', age=21)
  assert 'name' in d
  assert len(d) == 2
  assert d['age'] == 21  # KeyError if missing
  assert d.get('absent_key', 'default_value') == 'default_value'
  d['age'] = 25
  d['absent_key'] = 3 # No KeyError for unknown key
  d.update({'tel' : 12345, 'family' : 'Smith'})  # Or d |= {...}
  del d['family']  # KeyError if missing
  
  for (key, value, key_value_tuple) in zip(d.keys(), d.values(), d.items()):
    assert key == key_value_tuple[0]
    assert value == key_value_tuple[1]

  assert {x: x**2 for x in range(3)}  == {0 : 0, 1 : 1, 2 : 4}
 
  assert {"a" : 1, "b" : 2} | {"c" : 3} == {"a" : 1, "b" : 2, "c" : 3}
dictionaries()

def sets():
  s = {1, 2, 3}
  assert s == set([1, 2, 3])
  s.add(4)
  s.update([5, 6])
  s.remove(3)  # KeyError if missing
  s.discard(10)  # No-op if missing
  
  assert {1, 2, 3, 4}.union({3, 4, 5, 6}) == {x for x in range(1, 7)}
  assert {1, 2, 3, 4}.intersection({3, 4, 5, 6}) == {3, 4}
  assert {1, 2, 3, 4}.symmetric_difference({3, 4, 5, 6}) == {1, 2, 5, 6}
  assert {1, 2, 3, 4}.difference({3, 4, 5, 6}) == {1, 2}  
  
  assert {1, 2}.issubset({1, 2, 3})  # Or {1, 2} <= {1, 2, 3}
  assert {1, 2, 3}.issuperset({1, 2})  # Or {1, 2, 3} >= {1, 2}
  assert {1, 2}.isdisjoint({3, 4})
sets()
  
def numbers():
  assert 5 / 2 == 2.5
  assert 5 // 2 == 2
numbers()

def printing():
  a = [1, 2, 3]
  i = 5
  print(a)  # [1, 2, 3]
  print(f"{a=} {i}")  # a=[1, 2, 3] 5
printing()
  
def new_syntax():
  if (length := len("walrus")) > 4:
    assert True
  status = "OK"
  match status:
    case "OK": assert True
    case "Erorr": assert False
new_syntax()
  
def typed_arguments(i : int, s : str) -> int:
  return len(s) + i
assert typed_arguments(2, "abc") == 5

lambda_func = lambda x : x**2
assert lambda_func(5) == 25

def args_passing_mode(i : int, a : list):
  i = -1
  a[0] = -1
value = 0
reference = [10, 20, 30]
args_passing_mode(value, reference)
assert value == 0 and reference[0] == -1 

def three_args_func(a, b, c):
  return a + b + c
packedArguments = [10, 20, 30]
assert three_args_func(*packedArguments) == 60

def generator(n : int):
  sum = 0
  for i in range(n):
    sum += i
    yield sum
assert [x for x in generator(3)] == [0, 1, 3]

class Dog:
  species = "Canine"  # static
  def __init__(self, name, age):
    self.name = name
    self.age = age  
  def bark(self):
    return f"{self.name} says woof!"
class GoldenRetriever(Dog):
  def speak(self):
    return f"{super().bark()} and wags tail."
dog = Dog("Buddy", 3)

# TODO: 
# - exceptions
