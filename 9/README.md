## 代码规范

“Thus, programs must be written for people to read, and only incidentally for machines to execute.”
代码主要是为了写给人看的，只是附带的给机器运行

微软发明了一种变量命名法叫匈牙利命名法（Hungarian notation），在变量名中用前缀表示类型，例如iCnt（i表示int）、pMsg（p表示pointer）、lpszText（lpsz表示long pointer to a zero-ended string）等。Linus在[CodingStyle]中毫不客气地讽刺了这种写法：“Encoding the type of a function into the name (so-called Hungarian notation) is brain damaged - the compiler knows the types anyway and can check those, and it only confuses the programmer. No wonder MicroSoft makes buggy programs.”代码风格本来就是一个很有争议的问题，如果你接受本章介绍的内核编码风格（也是本书所有范例代码的风格），就不要使用大小写混合的变量命名方式[19]，更不要使用匈牙利命名法。


### 函数

每个函数都应该设计得尽可能简单，简单的函数才容易维护。应遵循以下原则：

实现一个函数只是为了做好一件事情，不要把函数设计成用途广泛、面面俱到的，这样的函数肯定会超长，而且往往不可重用，维护困难。

函数内部的缩进层次不宜过多，一般以少于4层为宜。如果缩进层次太多就说明设计得太复杂了，应考虑分割成更小的函数（Helper Function）来调用。

函数不要写得太长，建议在24行的标准终端上不超过两屏，太长会造成阅读困难，如果一个函数超过两屏就应该考虑分割函数了。[CodingStyle]中特别说明，如果一个函数在概念上是简单的，只是长度很长，这倒没关系。例如函数由一个大的switch组成，其中有非常多的case，这是可以的，因为各case分支互不影响，整个函数的复杂度只等于其中一个case的复杂度，这种情况很常见，例如TCP协议的状态机实现。

执行函数就是执行一个动作，函数名通常应包含动词，例如get_current、radix_tree_insert。

比较重要的函数定义上侧必须加注释，说明此函数的功能、参数、返回值、错误码等。

另一种度量函数复杂度的办法是看有多少个局部变量，5到10个局部变量已经很多了，再多就很难维护了，应该考虑分割成多个函数。

### indent工具

-kr选项表示K&R风格，-i8表示缩进8个空格的长度。如果没有指定-nut选项，则每8个缩进空格会自动用一个Tab代替。注意indent命令会直接修改原文件，而不是打印到屏幕上或者输出到另一个文件，这一点和很多UNIX命令不同。可以看出，-kr -i8两个选项格式化出来的代码已经很符合本章介绍的代码风格了，添加了必要的缩进和空白，较长的代码行也会自动折行。美中不足的是没有添加适当的空行，因为indent工具也不知道哪几行代码在逻辑上是一组的，空行还是要自己动手添，当然原有的空行肯定不会被indent删去的。