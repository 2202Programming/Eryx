#include "WPILib.h"

class ArtificialSource: public PIDSource
{
public:
	ArtificialSource()
	{
		DifferenceValue = 0;
	}
	~ArtificialSource()
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
	~ArtificialOutput()
	{

	}

	double OutputValue;

	void PIDWrite(float output)
	{
		OutputValue = (double)output;
	}
};
