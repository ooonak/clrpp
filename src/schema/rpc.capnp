@0x95939a40ab41b0e7;

struct MethodRegister {
  methodName @0: Text;
}

struct MethodCall {
  methodName @0: Text;
  args @1: List(Text);
}

struct MethodReturn {
  result @0: Text;
}
