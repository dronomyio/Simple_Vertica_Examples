/* Copyright (c) 2007 EntIT Software LLC, a Micro Focus company  -*- C++ -*-
 *
 * Description: Example User Defined Scalar Function: Add 2 ints
 *
 * Create Date: Apr 29, 2011
 */
#include "Vertica.h"

class exception;
using namespace Vertica;

// Remove our vt_throw_exception definition since Vertica.cpp provides it

/*
 * This is a simple function that adds two integers and returns the result
 */
class Add2Ints : public ScalarFunction
{
public:

    /*
     * This method computes the output range for this scalar function from
     *   the ranges of its inputs in a single invocation.
     *
     * The input ranges are retrieved via inRange
     * The output range is returned via outRange
     */
    virtual void getOutputRange(Vertica::ServerInterface &srvInterface,
                                Vertica::ValueRangeReader &inRange,
                                Vertica::ValueRangeWriter &outRange)
    {
        if (inRange.hasBounds(0) && inRange.hasBounds(1)) {
            // Input ranges have bounds defined
            if (inRange.isNull(0) || inRange.isNull(1)) {
                // At least one range has only NULL values.
                // Output range can only have NULL values.
                outRange.setNull();
                outRange.setHasBounds();
                return;
            } else {
                // Compute output range
                const vint& a1LoBound = inRange.getIntRefLo(0);
                const vint& a2LoBound = inRange.getIntRefLo(1);
                outRange.setIntLo(a1LoBound + a2LoBound);

                const vint& a1UpBound = inRange.getIntRefUp(0);
                const vint& a2UpBound = inRange.getIntRefUp(1);
                outRange.setIntUp(a1UpBound + a2UpBound);
            }
        } else {
            // Input ranges are unbounded. No output range can be defined
            return;
        }

        if (!inRange.canHaveNulls(0) && !inRange.canHaveNulls(1)) {
            // There cannot be NULL values in the output range
            outRange.setCanHaveNulls(false);
        }

        // Let Vertica know that the output range is bounded
        outRange.setHasBounds();
    }

    /*
     * This method processes a block of rows in a single invocation.
     *
     * The inputs are retrieved via argReader
     * The outputs are returned via resWriter
     */
    virtual void processBlock(ServerInterface &srvInterface,
                              BlockReader &argReader,
                              BlockWriter &resWriter)
    {
        try {
            // While we have inputs to process
            do {
                if (argReader.isNull(0) || argReader.isNull(1)) {
                    resWriter.setNull();
                } else {
                    const vint a = argReader.getIntRef(0);
                    const vint b = argReader.getIntRef(1);
                    resWriter.setInt(a+b);
                }
                resWriter.next();
            } while (argReader.next());
        } catch(std::exception& e) {
            // Standard exception. Quit.
            vt_report_error(0, "Exception while processing block: [%s]", e.what());
        }
    }
};

class Add2IntsFactory : public ScalarFunctionFactory
{
    // return an instance of Add2Ints to perform the actual addition.
    virtual ScalarFunction *createScalarFunction(ServerInterface &interface)
    { return vt_createFuncObject<Add2Ints>(interface.allocator); }

    virtual void getPrototype(ServerInterface &interface,
                              ColumnTypes &argTypes,
                              ColumnTypes &returnType)
    {
        argTypes.addInt();
        argTypes.addInt();
        returnType.addInt();
    }
};

RegisterFactory(Add2IntsFactory);

