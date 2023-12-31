/**
 * Jack Robbins
 * CS-280 Section 011
 * 11/15/2023
*/

#include <iostream>
#include <string>
#include "val.h"

using namespace std;

//division may occur only between ints and reals
Value Value::operator/(const Value& op) const{
switch(GetType()){
        //If we have an int, we can add with either a real or an int
        case VINT:
            if(op.GetType() == VINT){
                //we can have two ints, no casting needed
                return Value(GetInt() / op.GetInt());
            }

            if (op.GetType() == VREAL){
                //here we'll need to cast to the broader type
                return Value((float)GetInt() / op.GetReal());
            }

        //If we have an int, we can add with either a real or an int
        case VREAL:
            if(op.GetType() == VINT){
                //cast to a float
                return Value(GetReal() / (float)op.GetInt());
            }

            if (op.GetType() == VREAL){
                //no need for casting here
                return Value(GetReal() / op.GetReal());
            }

        default:
        //If we get here, this object was either a string or boolean and therefore invalid
            return Value();
    }
       
    //If we get here, op was either a string or a float and therefore invalid
    return Value();
}

//Comparing "this" with op
Value Value::operator==(const Value& op) const {
    //Check the cases for when types are equal first
    if (GetType() == op.GetType()){
        switch(GetType()){
            case VINT:
                return Value(GetInt() == op.GetInt());
            
            case VREAL:
                return Value(GetReal() == op.GetReal());
            
            case VSTRING:
                return Value(GetString() == op.GetString());

            case VBOOL:
                return Value(GetBool() == op.GetBool());

            default:
                //we should never get here in theory, added to avoid compile warnings on Vocareum
                return Value();
        }
    }
    
    //There are two special cases were we can mix ints and reals in either order
    if (IsReal() && op.IsInt()){
        //Cast op to be broader
        return Value(GetReal() == (float)op.GetInt());
    }

    if (IsInt() && op.IsReal()){
        //in this case cast the current object to be broader
        return Value((float)GetInt() == op.GetReal());
    }

    //If we get here, something went wrong so just return an empty value
    return Value();
}

//This ANDing operator is only valid for two booleans
Value Value::operator&&(const Value& oper) const{
    //If both types are not booleans, this will not work
    if(GetType() != VBOOL || oper.GetType() != VBOOL){
        return Value();
    }

    //If they are both booleans, simply use the boolean && operator
    return Value(GetBool() && oper.GetBool());

}

//Mod can only be performed on two ints, nothing else
Value Value::operator%(const Value& oper) const{
    //If both types are not int, this will not work
    if(GetType() != VINT || oper.GetType() != VINT){
        return Value();
    }
    //If we get here, we have two ints and this is valid
    return(GetInt() % oper.GetInt());
}
