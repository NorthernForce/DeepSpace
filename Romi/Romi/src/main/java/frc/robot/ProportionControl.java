package frc.robot;

public class ProportionControl 
{
    private double lastVal;
    private double steps = 5;

    public ProportionControl()
    {
      lastVal = 0;
    }
    
    public double prop(double val)
    {
      if (val < lastVal)
      {
        lastVal = lastVal - ((lastVal - val) / steps);
      }
      else if (val > lastVal)
      {
        lastVal = lastVal + ((val - lastVal) / steps);
      }
      else lastVal = val;
    
      return lastVal;
    } 
}
