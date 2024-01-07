# QueryTool
The QueryAppLib is a way to check whether a condition is true or false on some data.
The queries use SQL like syntax, and the data can be provided by writing a class derived from the ValueReceiver class, or using one of the two already existing classes derived from ValueReceiver, one of which is ValueReceiverJson that is for json files (loads all the data from a json file), or ValueReceiverLib which starts calean but can be populated with any sorts of data.

## QueryApp
The QueryApp is a simple demonstration of how it can be used, loading the data from a json the path for which it asks first, and then it can be queried multiple times.

## Example
Here is a basic example of how this tool can be used:
json j = json::parse("{\"x\":50 }");
ValueReceiverJson values(j);
Expression* exp = Expression::parse("x=50");
bool value = exp->get_value(&values);

The json can be as complicated as you wish, as well as the expression which can have many AND or OR operations (you better use paranthesis if you have many of those though). Text without Quotation marks is referred to as variables from the json (or any other form of forming the data depending on the class that derives the ValueReceiver class), while text with Quotation marks sets a set text. Numbes always represent numbers, and numeric expressions can have the greater then sign, equals sign or lesser then sign, while text comparisons can only be equal (and in case you want to query whether it isn't you can put the NOT boolean operator before that part of the query).

Future versions will make math expressions possible as well, as for now, unlike SQL or programming languages, it still cannot have numeric expressions like adding, multipyling, etc in the expression itself.
