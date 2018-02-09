public ArrayList<Point> Clipping_CyrusBeck(Point p1, Point p2, ArrayList<Point> boundary) {
    double upper = 1.0, lower = 0.0, dot1, dot2;
    Point boundarypoint1, boundarypoint2, normal, vector, direction = new Point((int)(p2.getX() - p1.getX()), (int)(p2.getY() - p1.getY()));
    for(int i = 0; i < boundary.size(); ++i) {
      boundarypoint1 = boundary.get(i);
      boundarypoint2 = boundary.get((i + 1) % boundary.size());
      normal = new Point((int)(boundarypoint1.getY() - boundarypoint2.getY()), (int)(boundarypoint2.getX() - boundarypoint1.getX()));
      vector = new Point((int)(-boundarypoint1.getX() + p1.getX()), (int)(-boundarypoint1.getY() + p1.getY()));
      dot1 = normal.getX() * direction.getX() + normal.getY() * direction.getY();
      dot2 = vector.getX() * normal.getX() + vector.getY() * normal.getY();
      if(dot1 > 0)
        lower = Math.max(lower, -dot2 / dot1);
      else if(dot1 < 0)
        upper = Math.min(upper, -dot2 / dot1);
      else if(dot2 < 0)
        return new ArrayList<Point>();
    }
    if(lower <= upper) {
      boundarypoint1 = new Point((int)(p1.getX() + lower * direction.getX()), (int)(p1.getY() + lower * direction.getY()));
      boundarypoint2 = new Point((int)(p1.getX() + upper * direction.getX()), (int)(p1.getY() + upper * direction.getY()));
      return Line_BresenhamIntegerGeneralized(boundarypoint1, boundarypoint2);
    }
    return new ArrayList<Point>();
  }