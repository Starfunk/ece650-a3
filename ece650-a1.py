import sys
import re

# A class object to store the lines we create with each street's set of points.
class Line:
      def __init__(self, p1, p2):
        self.p1 = p1
        self.p2 = p2
        self.x = "NA"
        if p2[0]- p1[0] == 0:
          self.m = 'v'
          self.b = 'v'
          self.x = p1[0]
        else:
          # Cast one of the integer to float
          self.m = (float(p2[1]) - p1[1]) / (p2[0]- p1[0])
          self.b = float(p1[1]) - self.m * p1[0]

# Returns the Euclidean distance between points p1 and p2.
def euclidean_distance(p1, p2):
  return ((p1[0]-p2[0]) ** 2 + (p1[1]-p2[1]) ** 2) ** (0.5)

# Returns the coordinates of the intersection between p1, p2, p3, and p4.
def check_intersection(p1, p2, p3, p4):
  line1 = Line(p1,p2)
  line2 = Line(p3,p4)
  if line2.m == line1.m
  # if line2.m == line1.m and line1.b != line2.b:
    return False
  #
  # # Don't handle overlaps. In this case, output that there is no intersection.
  # elif line2.m == line1.m and line1.b == line2.b:
  #   return False


  elif line1.m == 'v':
    x = line1.x
    y = line2.m * x + line2.b
  elif line2.m == 'v':
    x = line2.x
    y = line1.m * x + line1.b
  else:
    x = (float(line2.b)-line1.b) / (line1.m - line2.m)
    y = line1.m * x + line1.b
  if y > max(line1.p1[1], line1.p2[1]) or y < min(line1.p1[1], line1.p2[1]):
    return False
  elif y > max(line2.p1[1], line2.p2[1]) or y < min(line2.p1[1], line2.p2[1]):
    return False
  return (x, y)

def build_graph(streets):
  street_list = streets.values()
  V = {}
  E = []
  # The dictionary I stores how many intersections occurred between each node p1 and p2, and p3 and p4.
  I = {}
  vertex_id = 1
  # Iterate through the first n-1 streets
  for i in range(len(street_list)-1):
    street1 = street_list[i]
    # From street i, iterate through connected nodes on that street. These are the jth node and j+1th node.
    for j in range(len(street1) - 1):
      p1 = street1[j]
      p2 = street1[j+1]
      # A counter that first selects the i+1th street and
      # then iterates until the nth street.
      street_count = i + 1
      # Do actions in this while loop while we haven't #finished comparing p1 and p2 with
      # every valid pair of nodes from the i+1 street to
      # the nth street.
      while street_count <= len(street_list) - 1:
        street2 = street_list[street_count]
        # Iterate through all valid node pairs in street2
        # and compare with p1 and p2.
        for k in range(len(street2) - 1):
          p3 = street2[k]
          p4 = street2[k+1]
          if p3 == p1 and p4 == p2:
            sys.stderr.write("Error: Two streets share the same exact coordinates. Please reenter these two streets as one street!\n")
            break
          if p3 == p2 and p4 == p1:
            sys.stderr.write("Error: Two streets share the same exact coordinates. Please reenter these two streets as one street!\n")
            break
          intersection = check_intersection(p1, p2, p3, p4)
          # If there is an intersection, add the
          # nodes that have not already been added to the
          # vertices dictionary to the dictionary,
          # including the intersection node.
          if intersection:
            intersection = (round(intersection[0], 3),round(intersection[1], 3))
            V_values = V.values()
            if intersection in V_values:
              for key, value in V.items():
                if value == intersection:
                  intersection_id = key
                  break

            V_values = V.values()
            if not intersection in V_values:
              V[vertex_id] = intersection
              intersection_id = vertex_id
              vertex_id = vertex_id + 1

            V_values = V.values()
            if p1 in V_values:
              for key, value in V.items():
                if value == p1:
                  p1_id = key
                  break
            if not p1 in V_values:
              V[vertex_id] = p1
              p1_id = vertex_id
              vertex_id = vertex_id + 1

            V_values = V.values()
            if p2 in V_values:
              for key, value in V.items():
                if value == p2:
                  p2_id = key
                  break
            if not p2 in V_values:
              V[vertex_id] = p2
              p2_id = vertex_id
              vertex_id = vertex_id + 1

            # Make sure that the edge is unique and that the point is not equal to the intersection!
            if not (p1_id, intersection_id) in E and p1 != intersection:
              E.append((p1_id, intersection_id))
            if not (p2_id, intersection_id) in E and p2 != intersection:
              E.append((p2_id, intersection_id))
            if (p1_id,p2_id) in I.keys():
              d = euclidean_distance(p1, intersection)
              I[(p1_id,p2_id)][intersection_id] = d
            if not (p1_id,p2_id) in I.keys():
              d = euclidean_distance(p1, intersection)
              I[(p1_id,p2_id)] = {intersection_id: d}
            V_values = V.values()
            if p3 in V_values:
              for key, value in V.items():
                if value == p3:
                  p3_id = key
                  break
            if not p3 in V_values:
              V[vertex_id] = p3
              p3_id = vertex_id
              vertex_id = vertex_id + 1
            V_values = V.values()
            if p4 in V_values:
              for key, value in V.items():
                if value == p4:
                  p4_id = key
                  break
            if not p4 in V_values:
              V[vertex_id] = p4
              p4_id = vertex_id
              vertex_id = vertex_id + 1
            if not (p3_id, intersection_id) in E and p3 != intersection:
              E.append((p3_id, intersection_id))
            if not (p4_id, intersection_id) in E and p4 != intersection:
              E.append((p4_id, intersection_id))

            if (p3_id,p4_id) in I.keys():
              d = euclidean_distance(p3, intersection)
              I[(p3_id,p4_id)][intersection_id] = d
            if not (p3_id,p4_id) in I.keys():
                d = euclidean_distance(p3, intersection)
                I[(p3_id,p4_id)] = {intersection_id: d}

        # Iterate the street counter by 1 so we are comparing p1 and p2
        # to the nodes in the next street in street_list.
        street_count = street_count + 1

  # Each key is the tuple (p1,p2) and each value is
  # a dictionary of intersection id and distance to p1
  # key-value pairs.
  # E.g. key ((1,3),(2,4)), and value {1: 3, 2: 1}
  # It looks like this: I[(p3_id,p4_id)] = {intersection_id: d}
  for key, value in I.items():
    if len(value.values()) >= 2:
      p1 = key[0]
      p2 = key[1]

      # If euclidean distance is equal to 0
      # then p1 is an intersection
      # if euclidean distance is equal to max
      # distance . then p2 is an intersection

      # key2 is the vertex id of each intersection
      # value2 is the euclidean distance from the
      # intersection to p1

      # Returns a sorted array of tuples, sorted
      # by the second value in the array. In this, case the tuple is (intersection_id, distance to p1).
      # The sort is in terms of the distance from the intersection to p1.
      sorted_value = sorted(value.items(), key=lambda x: x[1])

      # This loop removes all the intersections in E that are also in
      # sorted_value, which represents a list that tells us what the order
      # of intersections is and thus which nodes are connected.
      for i in range(len(sorted_value)):
        if (p1, sorted_value[i][0]) in E:
          E.remove((p1, sorted_value[i][0]))
        if (p2, sorted_value[i][0]) in E:
          E.remove((p2, sorted_value[i][0]))

      # We then add the edges back into E with the correct connections between nodes.

      # This is the case where the first intersection is
      # equal to the point p1 and there are two intersections.
      if (sorted_value[0][1]) == 0 and len(sorted_value) == 2:
        # We say the first intersection is p1 with the second intersection_id,
        # since the first intersection_id has the same coordinates as p1.
        # Second tuple's intersection_id
        intersection1 = (p1, sorted_value[1][0])
        E.append(intersection1)
        E.append((sorted_value[1][0],p2))

      # This is the case where the first intersection is
      # equal to the point p1 and there are more than two intersections.
      elif (sorted_value[0][1]) == 0 and len(sorted_value) > 2:
        # We say the first intersection is p1 with the second intersection_id,
        # since the first intersection_id has the same coordinates as p1.
        intersection1 = (p1, sorted_value[1][0])
        E.append(intersection1)
        for j in range(len(sorted_value)-2):
            E.append((sorted_value[j+1][0],sorted_value[j+2][0]))
            if j == len(sorted_value) - 3:
              # Shouldn't we test if the final intersection is equal to p2?
              # TODO
              E.append((sorted_value[j+2][0],p2))
              break
        # This is the case where the first intersection is
        # not equal to the point p1.
      else:
        intersection1 = (p1, sorted_value[0][0])
        E.append(intersection1)
        for i in range(len(sorted_value)):
          if i == len(sorted_value) - 1:
            E.append((sorted_value[i][0],p2))
            break
          E.append((sorted_value[i][0],sorted_value[i+1][0]))

  E_clean = list(dict.fromkeys(E))
  return (V,E_clean)

def main():
    streets = {}
    # r = check_intersection((-3,-2),(-3,0),(-3,0),(2,2))
    # print(r)

    while True:
      try:
        arg = raw_input()
      except EOFError:
        sys.exit(0)

      #line = sys.stdin.readline()
      line = arg

      # if line == "RGEN FINISHED\n":
      #   sys.stdout.write("A1 FINISHED\n")
      #   sys.stdout.flush()
      #   sys.exit(0)


      user_input = re.compile("([acrg])\s(\".+\")\s").split(line)

      if len(user_input) == 1:
        # Handle the command = 'r' case here.
        if user_input[0][0] == 'r':
          format_user_input = re.compile("(\".+\")")     .split(line)

          street_name_r = format_user_input[1]
          try:
            del streets[street_name_r]
            continue
          except:
            sys.stderr.write("Error: " + street_name_r + " does not exist.\n")
            continue



        else:
          command_list = re.findall('^g$', user_input[0])

          try:
            command = command_list[0]
            if command[0] != 'g':
              sys.stderr.write("Error: Invalid input.\n")
              continue

          except:
            sys.stderr.write("Error: Invalid input.\n")
            continue
      else:
        command = re.sub('[^acr]',"", user_input[1])
        if len(command) == 0 or len(command) > 1:
          sys.stderr.write("Error: Invalid input.\n")
          continue

        street_name = user_input[2]
        street_name_test = []
        # Regex doesn't return the proper string if the length of the string is less than 4, so if the string's length is less than 4 we manually feed it into the next stage of formatting.
        if len(street_name) <= 4:
          street_name_test.append(street_name)
        else:
          street_name_test = re.findall("\"[^\s].+[^\s]\"", line)

        try:
          if street_name_test[0] != user_input[2]:
            sys.stderr.write("Error: Invalid street name.\n")
            continue
        except:
          sys.stderr.write("Error: Invalid street name.\n")
          continue
        # Test if street name has special characters in it
        street_name_test2 = re.findall("[^a-zA-Z\s\"]", user_input[2])
        street_name_test2.append(0)
        if len(street_name_test2) > 1:
          sys.stderr.write("Error: Only alphabetical characters are allowed for street names.\n")
          continue
        # Street names are case-insensitive
        # This guarantees that if the same name is used
        # but in a different case, it gets matched to
        # how it was originally entered.
        for key in streets.keys():
          # Need to format both strings to contain no spaces and no quotes so that we can compare them
          # Note that this does open up potential errors if the spaces are not aligned. This should be fixed in the future!
          format_street_name = re.findall('[^"\s]+',street_name)
          format_key = re.findall('[^"\s]+',key)
          try:
            if format_street_name[0].lower() == format_key[0].lower():
              street_name = key
              if command == 'a':
                sys.stderr.write("Error: Please use the command 'c' or 'r' to change streets that have already been input.\n")
              break
          except:
            sys.stderr.write("Error: Invalid street name.\n")

        coordinates = user_input[3]

        no_space_coordinates = re.sub('\s',"",coordinates)

        coordinates_test = re.findall("^((\(-?\d*\,-?\d*\))*)$", no_space_coordinates)
        format_coordinates = re.sub("\s","", user_input[3])

        try:
          if coordinates_test[0][0] != format_coordinates:
            sys.stderr.write("Error: Invalid coordinates.\n")
            continue
        except:
          sys.stderr.write("Error: Invalid coordinates.\n")
          continue


      if command == 'a':
        if user_input[2][0] == " " or user_input[2][len(user_input[2])-1] == " ":
          sys.stderr.write("Error: Spaces are not allowed at the beginning or end of the street name.\n")
          continue
        t = re.findall('-?\d?\d+', user_input[3])
        vertices = []
        counter = 0
        for i in range(len(t)/2):
          vertices.append((int(t[i + counter]),int(t[i + counter + 1])))
          streets[street_name] = vertices
          counter = counter + 1

      elif command == 'c':
        try:
          del streets[street_name]
        except:
          sys.stderr.write("Error: " + street_name + " does not exist.\n")
          continue
        t = re.findall('-?\d?\d+', user_input[3])
        vertices = []
        counter = 0
        for i in range(len(t)/2):
          vertices.append((int(t[i + counter]),int(t[i + counter + 1])))
          streets[street_name] = vertices
          counter = counter + 1

      elif command == 'g':
        if len(streets.values()) == 0:
          sys.stderr.write("Error: No streets have been specified.\n")
          continue
        else:
          t = build_graph(streets)

          sys.stdout.write("V " + str(len(t[0])) + "\n")



          sys.stdout.write("E {")

          for i in range(len(t[1])):
            if i < len(t[1]) - 1:
              sys.stdout.write("<" + str(t[1][i][0]-1) + "," + str(t[1][i][1]-1)+ ">,")

            elif i == len(t[1]) - 1:
              sys.stdout.write("<" + str(t[1][i][0]-1) + "," + str(t[1][i][1]-1)+ ">}\n")

        sys.stdout.flush()


    print 'Finished reading input'
    # return exit code 0 on successful termination
    sys.exit(0)

if __name__ == '__main__':
    main()
