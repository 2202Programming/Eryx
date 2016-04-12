#include "WPILib.h"

class ArtificialSource: public PIDSource
{
public:
	ArtificialSource()
	{
		DifferenceValue = 0;
	}
	virtual ~ArtificialSource()
	{

	}

	ArtificialSource(double x)
	{
		DifferenceValue = x;
	}

	double PIDGet()
	{
		return DifferenceValue;
	}

	void SetDiffence(double x)
	{
		DifferenceValue = x;
	}

private:
	double DifferenceValue;
};

class ArtificialOutput: public PIDOutput
{
public:
	ArtificialOutput()
	{
		OutputValue = 0.0;
	}
	virtual ~ArtificialOutput()
	{

	}

	double OutputValue;

	void PIDWrite(float output)
	{
		OutputValue = (double)output;
	}
};
