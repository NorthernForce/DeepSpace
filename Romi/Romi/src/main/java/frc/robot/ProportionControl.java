package frc.robot;

public class ProportionControl 
{
    private double lastVal;

    public ProportionControl()
    {
      lastVal = 0;
    }
    
    public double prop(double val)
    {
      if (val < lastVal)
      {
        lastVal = lastVal - ((lastVal - val) / 5);
      }
      else if (val > lastVal)
      {
        lastVal = lastVal + ((val - lastVal) / 5);
      }
      else lastVal = val;
    
      return lastVal;
    } 
}
