using System;
using System.IO;

namespace reading
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Trying to read the code!");
            Reader test = new Reader("../../../model.ALI");

            // Read the file present in the path
            using (StreamReader sr = new StreamReader("../../../model.ALI"))
            {

                // Iterating the file
                while (sr.Peek() >= 0)
                {

                    // Read the data in the file until the peak

                    // checking if the peak of the char is working
                    bool mal = test.NextElementIsMaterial();
                    bool lig = test.NextElementIsLight();
                    bool mesh = test.NextElementIsMesh();

                  
                    // testing to see if it iis a material and looking at data
                    if (mal)
                    {
                        MaterialData md = test.NextMaterial();
                        Console.WriteLine(md.ToString());
                        Console.WriteLine("name: " + md.name);
                        Console.WriteLine("is T: " + md.isTransparent);
                        Console.WriteLine("red color: " + md.mainColor.r);
                        Console.WriteLine("green color: " + md.mainColor.g);
                        Console.WriteLine("blue color: " + md.mainColor.b);
                        Console.WriteLine("color aph: " + md.mainColor.a);
                        Console.WriteLine(""); //adding spacer

                    }

                    if (lig) {

                        LightData lightData = test.NextLight();
                        Console.WriteLine("light int: " + lightData.intensity) ;
                        Console.WriteLine(""); //adding spacer
                    }
                    if (mesh) {
                        MeshData meshData = test.NextMesh();
                        Console.WriteLine("mesh name: " + meshData.name);

                        meshData.submeshes.ForEach(p => Console.WriteLine(p.materialName));
                        Console.WriteLine(""); //adding spacer


                    }

                }
            }




        }
    }
}
