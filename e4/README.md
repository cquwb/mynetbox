1. 实现reactor模式
2. EventHandler的修改总结：
- 使用智能指针，并且禁止原始对象的拷贝和赋值。
- 事件处理的mLoopIdex成员主要是为了将来unregister的时候快速定位到自己的位置的。是属于数据结构成面的设计
- 使用友元函数而不是类的成员函数来做注册方法没太了解 
3. PollLoop修改总结
- 为什么使用友元函数，就是为了不在loop类的register里面既做register也做修改handler.loopIdx的操作。
- handler本身也不能对外提供public的setidx的方法。
