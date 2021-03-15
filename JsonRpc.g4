grammar JsonRpc;

parse: json EOF;

json: msg | '[' msg (',' msg)* ']';

msg: '{' msgField (',' msgField)* '}';

msgField: version | id | method | result | error | params;

version: '"jsonrpc"' ':' STRING;

id: '"id"' ':' (STRING | NUMBER | 'null');

method: '"method"' ':' STRING;

params: '"params"' ':' (obj | arr);

error: '"error"' ':' errorObj;

result: '"result"' ':' value;

pair: STRING ':' value;

obj: '{' pair (',' pair)* '}' | '{' '}';

errorObj: '{' errorField (',' errorField)* '}';

errorField: code | message | data;

code: '"code"' ':' NUMBER;

message: '"message"' ':' STRING;

data: '"data"' ':' value;

arr: '[' value (',' value)* ']' | '[' ']';

value: STRING | NUMBER | obj | arr | 'true' | 'false' | 'null';

fragment ESC: '\\' (["\\/bfnrt] | UNICODE);

fragment UNICODE: 'u' HEX HEX HEX HEX;

fragment HEX: [0-9a-fA-F];

fragment SAFECODEPOINT: ~ ["\\\u0000-\u001F];

fragment INT: '0' | [1-9] [0-9]*;

// no leading zeros

fragment EXP: [Ee] [+\-]? INT;

// \- since - means "range" inside [...]

STRING: '"' (ESC | SAFECODEPOINT)* '"';

NUMBER: '-'? INT ('.' [0-9]+)? EXP?;

WS: [ \t\n\r]+ -> skip;
