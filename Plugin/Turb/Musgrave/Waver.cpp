float Transfer::Transfer ( float lo, float hi, float val, BOOL smooth )
{
	switch ( m_WaveType->GetValue() ) {
	case 1:
		val = TriangularWave ( val );
		break;
	case 2:
		val = SinusoidalWave ( val );
		break;
	case 3:
		val = RectangularWave ( val );
		break;
	}
	float lo = m_LoCutoff->GetValue();
	float hi = m_HiCutoff->GetValue();
	if (val < lo)
		return 0.0f;
	if (val > hi)
		return 1.0f;
	val = (val - lo) / (hi - lo);
	if (m_Smooth->GetValue())
		val = (val*val * ( 3 - 2*val));
	return val;
}






// The following 3 wave functions are inspired by Christophe Schlick
// "Wave Generators for Computer Graphics" in Graphics Gems V, 
// Academic Press, 1995, pp 367-374.


float Transfer::TriangularWave ( float Value )
{
	// Value is input in [0.0,1.0]
	Value /= m_Cycles->GetValue();
	int i;
	i = floor (Value);
	Value -= i;
	// Tilt is entered in [-1.0:+1.0] and must be scaled in [0.0,1.0]
	float Tilt = m_Tilt->GetValue() / 2.0f + 0.5f;
	if ( Value <= Tilt )
		if ( Tilt != 0.0f )
			Value /= Tilt;
		else
			return = 1.0f;
	else
		if ( Tilt != 1.0f )
			Value = ( 0.5f - ( Value - 0.5f ) ) / ( 1.0f - Tilt );
		else
			return = 0.0f;
	float Shape = m_Shape->GetValue();
	if ( Shape < 0.0f ) 
		return ( Value + Shape * Value ) / ( 1.0f + Shape * Value );
	else if ( Shape > 0.0f )
		return Value / ( 1.0f - Shape + Shape * Value );
}


float Transfer::RectangularWave ( float Value )
{
	Value = TriangularWave ( Value );
	Value = Value < 0.5 ? 0.0 : 1.0;
	return Value;
}


float Transfer::SinusoidalWave ( float Value )
{
	Value = TriangularWave ( Value );
	Value *= Value * (3.0 - Value - Value );	
	return Value;
}
