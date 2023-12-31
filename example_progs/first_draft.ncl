canvas(color(255, 255, 255), "test_name.png", 1000, 1000) {
  # Axiom Shapes
  rect = rectangle(1.0, 1.0, point(30.0, 30.0))
  circ = circle(1.0, point(1.0, 1.0))
  ell = ellipse(15.0, 17.0, point(1.0, 1.0))
  sq = square(1.0, point(30.0, 15.0))
  # Useful Functions
  rect_1 = rectangle(1.0, 1.0, south(x))
  rect_2 = rectangle(1.0, 1.0, south(x))
  line(from(rect_1), to(rect_2))
  # Example of Making Graph Structure
  root = circle(1.0, point(1.0, 1.0))
  children = [circle(1.0, point(3.0, 3.0))]
  # Loop
  for i in range(1, 8) {
    append(z, circle(1.0, west(z[i - 1])))
    line(from(q), to(z[i - 1]))
  }

  # Write Everything
  write(rect)
  write(circ)
  write(ell)
  write(sq)
  write(rect_1)
  write(rect_2)
  write(root)
  for i in range(8) {
    write(z[i])
  }
}
