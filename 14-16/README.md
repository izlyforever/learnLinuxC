## 数据类型详解

As far as the committee knows, all machines treat all bits zero as a representation of floating-point zero. But, all bits zero might not be the canonical representation of zero. 因此在绝大多数平台上，一个浮点数的所有bit是0就表示0值。

C标准的Rationale之一：优先考虑效率，而可移植性尚在其次

### 浮点数

C标准规定的浮点型有float、double、long double，和整型一样，既没有规定每种类型占多少字节，也没有规定采用哪种表示形式。浮点数的实现在各种平台上差异很大，有的处理器有浮点运算单元（FPU，Floating Point Unit），称为硬浮点（Hard-float）实现；有的处理器没有浮点运算单元，只能做整数运算，需要用整数运算来模拟浮点运算，称为软浮点（Soft-float）实现。大部分平台的浮点数实现遵循IEEE 754，float型通常是32位，double型通常是64位。

long double型通常是比double型精度更高的类型，但各平台的实现有较大差异。在x86平台上，大多数编译器实现的long double型是80位，因为x86的浮点运算单元具有80位精度，gcc实现的long double型是12字节（96位），这是为了对齐到4字节边界（在第 4 节 “结构体和联合体”详细讨论对齐的问题），也有些编译器实现的long double型和double型精度相同，没有充分利用x86浮点运算单元的精度。其它体系结构的浮点运算单元的精度不同，编译器实现也会不同，例如PowerPC上的long double型通常是128位。

以前我们只用到最简单的浮点数常量，例如3.14，现在看看浮点数常量还有哪些写法。由于浮点数在计算机中的表示是基于科学计数法的，所以浮点数常量也可以写成科学计数法的形式，尾数和指数之间用e或E隔开，例如314e-2表示314×10-2，注意这种表示形式基数是10[27]，如果尾数的小数点左边或右边没有数字则表示这一部分为零，例如3.e-1，.987等等。浮点数也可以加一个后缀，例如3.14f、.01L，浮点数的后缀和类型之间的对应关系比较简单，没有后缀的浮点数常量是double型的，有后缀f或F的浮点数常量是float型的，有后缀l或L的浮点数常量是long double型的。

### 自动类型转化

3.2. Usual Arithmetic Conversion
两个算术类型的操作数做算术运算，比如a + b，如果两边操作数的类型不同，编译器会自动做类型转换，使两边类型相同之后才做运算，这称为Usual Arithmetic Conversion。转换规则如下：

如果有一边的类型是long double，则把另一边也转成long double。

否则，如果有一边的类型是double，则把另一边也转成double。

否则，如果有一边的类型是float，则把另一边也转成float。

否则，两边应该都是整型，首先按上一小节讲过的规则对a和b做Integer Promotion，然后如果类型仍不相同，则需要继续转换。首先我们规定char、short、int、long、long long的转换级别（Integer Conversion Rank）一个比一个高，同一类型的有符号和无符号数具有相同的Rank。转换规则如下：

如果两边都是有符号数，或者都是无符号数，那么较低Rank的类型转换成较高Rank的类型。例如unsigned int和unsigned long做算术运算时都转成unsigned long。

否则，如果一边是无符号数另一边是有符号数，无符号数的Rank不低于有符号数的Rank，则把有符号数转成另一边的无符号类型。例如unsigned long和int做算术运算时都转成unsigned long，unsigned long和long做算术运算时也都转成unsigned long。

剩下的情况是：一边有符号另一边无符号，并且无符号数的Rank低于有符号数的Rank。这时又分为两种情况，如果这个有符号数类型能够覆盖这个无符号数类型的取值范围，则把无符号数转成另一边的有符号类型。例如遵循LP64的平台上unsigned int和long在做算术运算时都转成long。

否则，也就是这个有符号数类型不足以覆盖这个无符号数类型的取值范围，则把两边都转成有符号数的Rank对应的无符号类型。例如在遵循ILP32的平台上unsigned int和long在做算术运算时都转成unsigned long。

可见有符号和无符号整数的转换规则是十分复杂的，虽然这是有明确规定的，不属于阴暗角落，但为了程序的可读性不应该依赖这些规则来写代码。我讲这些规则，不是为了让你用，而是为了让你了解有符号数和无符号数混用会非常麻烦，从而避免触及这些规则，并且在程序出错时记得往这上面找原因。所以这些规则不需要牢记，但要知道有这么回事，以便在用到的时候能找到我书上的这一段。

到目前为止我们学过的+ - * / % > < >= <= == !=运算符都需要做Usual Arithmetic Conversion，因为都要求两边操作数的类型一致，在下一章会介绍几种新的运算符也需要做Usual Arithmetic Conversion。单目运算符+ - ~只有一个操作数，移位运算符<< >>两边的操作数类型不要求一致，这些运算不需要做Usual Arithmetic Conversion，但也需要做Integer Promotion，运算符~ << >>将在下一章介绍。
