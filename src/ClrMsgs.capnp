@0x9cc0373c47f2f0b2;

struct MethodRegister {
  seqNumber @0 :UInt64;
  clientId @1 :Text;
  methodName @2 :Text;
  argumentTypes @3 :List(Text);   # Captures argument types
}

struct Argument {
  union {
    intValue @0 :Int64;
    floatValue @1 :Float64;
    textValue @2 :Text;
    binaryValue @3 :Data;
  }
}

struct MethodCall {
  seqNumber @0 :UInt64;
  methodName @1 :Text;
  arguments @2 :List(Argument);
}

struct MethodReturn {
  seqNumber @0 :UInt64;
  success @1 :Bool;
  result @2: AnyPointer;
}
