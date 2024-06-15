#include "./eosRuler.hh"

  eosRuler::eosRuler()
  {

    division=1;
    scaleLength=10;
    scaleRadius=0.1;
    scaleFace=20;

    divisionFace=20;
    divisionLength=0.05;
    divisionRadius=0.5;

    mark=5;
    markLength=0.05;
    markRadius=0.8;

    reset();

  }


  void eosRuler::reset()
  {
    divisionNumber = (int)(scaleLength / division);
  }


//Ikutu-me de Ookina cylinder wo show suruka?

void eosRuler::SetMark(int m)
{
  mark = m;
  reset();
}

//Scale no Length
void eosRuler::SetScaleLength(double l)
{
  scaleLength = l;
  reset();
}

//Memori no Kugiri-Size
void eosRuler::SetDivision(double d)
{
  division = d;
  reset();
}

  void eosRuler::Draw(vtkRenderer* renderer)
{

	ren = renderer;
	Draw();

}



  void eosRuler::Draw()
{ 
 int i;

 assembly = vtkAssembly::New();

    //Cylinder
    rulerAxis = vtkCylinderSource::New();
    rulerAxis->SetHeight(scaleLength);
    rulerAxis->SetRadius(scaleRadius);
    rulerAxis->SetCenter(0,0,0);
    rulerAxis->SetResolution(scaleFace);
    rulerAxisMapper = vtkPolyDataMapper::New();
    rulerAxisMapper->SetInput(rulerAxis->GetOutput());
    rulerAxisActor = vtkActor::New();
    rulerAxisActor->SetMapper(rulerAxisMapper);
    
    rulerAxisActor->GetProperty()->SetColor(0.8,0.4,0.6);
    rulerAxisActor->RotateZ(90);
    rulerAxisActor->SetPosition(scaleLength/2,0,0);
    //axisTActor->SetPosition(0,0,0);


    //ren->AddActor(rulerAxisActor);
    
    assembly->AddPart(rulerAxisActor);


    for(i=0 ; i<=divisionNumber ; i++)
      {

    ruler = vtkCylinderSource::New();

    if(i%mark==0){

    ruler->SetHeight(markLength);
    ruler->SetRadius(markRadius);

    }
    else{

    ruler->SetHeight(divisionLength);
    ruler->SetRadius(divisionRadius);

    }


    //rulerSpace->SetHeight(divisionLength);
    //rulerSpace->SetRadius(divisionRadius);
 
    ruler->SetCenter(0,0,0);
    
    ruler->SetResolution(divisionFace);
    rulerMapper = vtkPolyDataMapper::New();
    rulerMapper->SetInput(ruler->GetOutput());
    rulerActor = vtkActor::New();
    rulerActor->SetMapper(rulerMapper);
    
    rulerActor->GetProperty()->SetColor(0.3,0.5,0.7);
    rulerActor->RotateZ(90);
    rulerActor->SetPosition(i*division,0,0);
 
    assembly->AddPart(rulerActor);
   
    //ren->AddActor(rulerActor);
    
    
      }

    assembly->SetOrigin(0,0,0);
    assembly->RotateY(90);
    assembly->SetPosition(5,5,5);
    ren->AddActor(assembly);


}

