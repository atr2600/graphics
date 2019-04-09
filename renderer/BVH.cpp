//
// Created by khan on 4/6/19.
//

//#include <algorithm>
#include <algorithm>
#include <cfloat>
#include "BVH.h"
#include "Shape.h"


BVH::BVH(std::vector<Shape *> BVHs, int h) {
    //Check size for 1 or 2
    // Then you can just set the child to left and right
    // this is the osrt section
    bounds[0] = sivelab::Vector3D(DBL_MAX,DBL_MAX,DBL_MAX);
    bounds[1] = sivelab::Vector3D(-DBL_MAX,-DBL_MAX,-DBL_MAX);
    if(BVHs.size()==1){
        isthisabox=true;
        name = "BoundingBox";
        min = BVHs[0]->getMin();
        max = BVHs[0]->getMax();
        bounds[0] = min;
        bounds[1] = max;
        mid = max - min;
        isthisabox=false;
        leftChild = BVHs[0];
        rightChild = nullptr;
    } else if(BVHs.size()==2){
        isthisabox=true;
        name = "Bounding Box";
        leftChild = BVHs[0];
        rightChild = BVHs[1];
        rightChild->isthisabox=false;
        leftChild->isthisabox=false;
        minOrMax(leftChild,rightChild);
        mid = max - min;

    } else{
        isthisabox=true;
        name = "Bounding Box";
        if(h == 0) std::sort(BVHs.begin(),BVHs.end(), compareItX);
        if(h == 1) std::sort(BVHs.begin(),BVHs.end(), compareItY);
        if(h == 2) std::sort(BVHs.begin(),BVHs.end(), compareItZ);
        std::vector<Shape*> leftB(BVHs.begin(),BVHs.begin()+BVHs.size()/2);
        std::vector<Shape*> rightB((BVHs.begin()+BVHs.size()/2),BVHs.end());
        leftChild = new BVH(leftB,h+1);
        rightChild = new BVH(rightB,h+1);
        minOrMax(leftChild,rightChild);
        mid = max - min;
    }


}










void BVH::minOrMax(Shape *l, Shape*r){
    Vector3D lmin = l->getMin();
    Vector3D rmin = r->getMax();
    Vector3D lmax = l->getMax();
    Vector3D rmax = r->getMax();


    for(int i = 0; i < 3;i++){
        if(lmin[i]<rmin[i]){
            min[i] = lmin[i];
        } else min [i] = rmin[i];
        if(lmax[i]>rmax[i]){
            max[i]= lmax[i];
        } else max[i]= rmax[i];
    }
    bounds[0] = min;
    bounds[1] = max;
}

void BVH::setValues(Shape* child, std::vector<Shape*> tree) {
    //set min mid max variables
    //lowest low and highest max of left and right child.
    child->setXdim(sivelab::Vector3D(tree[0]->getXdim()));
    child->setYdim(sivelab::Vector3D(tree[0]->getYdim()));
    child->setZdim(sivelab::Vector3D(tree[0]->getZdim()));
    for(int i = 0; i<tree.size();i++){
        if(getXdim()[0]>tree[i]->getXdim()[0]){
            child->xdim[0] = getXdim()[0];
        }
        if(getXdim()[2]<tree[i]->getXdim()[2]){
            child->xdim[2] = getXdim()[2];
        }
        if(getYdim()[0]>tree[i]->getYdim()[0]){
            child->xdim[0] = getYdim()[0];
        }
        if(getYdim()[2]<tree[i]->getYdim()[2]){
            child->xdim[2] = getYdim()[2];
        }
        if(getZdim()[0]>tree[i]->getZdim()[0]){
            child->xdim[0] = getZdim()[0];
        }
        if(getZdim()[2]<tree[i]->getZdim()[2]){
            child->xdim[2] = getZdim()[2];
        }
    }
    child->xdim[1] = child->xdim[2]-child->xdim[0];
    child->ydim[1] = child->ydim[2]-child->ydim[0];
    child->zdim[1] = child->zdim[2]-child->zdim[0];

}

bool BVH::intersect(double tminArg, double &t, HitStruct &hit, Ray r) {
//    return leftChild->intersect(tminArg,t,hit,r);
//    color = leftChild->color;
 //   return true;
    float txmin, txmax, tymin, tymax, tzmin, tzmax, tmin, tmax;

    float txymin, txymax, txyzmin,txyzmax;

    if(r.getDirection()[0]>=0){
        txmin = min[0] - r.getOrigin()[0] / r.getDirection()[0];
        txmax = max[0] - r.getOrigin()[0] / r.getDirection()[0];
    }else{
        txmin = max[0] - r.getOrigin()[0] / r.getDirection()[0];
        txmax = min[0] - r.getOrigin()[0] / r.getDirection()[0];
    }
    if(r.getDirection()[1]>=0){
        tymin = min[1] - r.getOrigin()[1] / r.getDirection()[1];
        tymax = max[1] - r.getOrigin()[1] / r.getDirection()[1];
    }else{
        tymin = max[1] - r.getOrigin()[1] / r.getDirection()[1];
        tymax = min[1] - r.getOrigin()[1] / r.getDirection()[1];
    }

    txymin = (txmin < tymin ? txmin : tymin);
    txymax = (txmax > tymax ? txmin : tymin);

    if (txymin > txymax){
        return false;

    }

    if(r.getDirection()[2]>=0){
        tzmin = min[2] - r.getOrigin()[1] / r.getDirection()[2];
        tzmax = max[2] - r.getOrigin()[1] / r.getDirection()[2];
    }else{
        tzmin = max[2] - r.getOrigin()[2] / r.getDirection()[2];
        tzmax = min[2] - r.getOrigin()[2] / r.getDirection()[2];
    }

    txyzmin = (txymin < tzmin ? txymin : tzmin);
    txyzmax = (txymax > tzmax ? txymax : tzmax);

    if ( txyzmin > txyzmax){
        return false;
    }


//    setTvalue(tmin);
//    hit.setActualT(tmin);

    bool ifHit = false;
    bool ifHitRight = false;
    bool ifHitLeft = leftChild->intersect(tmin, t, hit, r);
    if(rightChild != nullptr){
       ifHitRight = rightChild->intersect(tmin,t, hit, r);
    }



    if((ifHitLeft)||(ifHitRight)) {
        ifHit = true;
        if(ifHitLeft&&ifHitRight){
            if(leftChild->getTvalue()>rightChild->getTvalue()){
                setName(leftChild->getColor());
            } else {
                setName(rightChild->getColor());
            }
        } else if(ifHitLeft){
            setName(leftChild->getColor());
        } else {
            setName(rightChild->getColor());
        }

    }


    return ifHit;
}



