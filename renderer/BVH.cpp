//
// Created by khan on 4/6/19.
//

//#include <algorithm>
#include <algorithm>
#include "BVH.h"



BVH::BVH(std::vector<Shape *> BVHs, int h) {
    //Check size for 1 or 2
    // Then you can just set the child to left and right
    // this is the osrt section

    if(BVHs.size()==1){
        sivelab::Vector3D min, max;
        min = BVHs[0]->getMax();
        max = BVHs[0]->getMax();
        xdim[0] = min[0];
        xdim[2] = max[0];
        xdim[1] = (max[0]+min[0]/2);
        ydim[0] = min[1];
        ydim[2] = max[1];
        ydim[1] = (max[1]+min[1]/2);
        zdim[0] = min[2];
        zdim[2] = max[2];
        zdim[1] = (max[2]+min[2]/2);
        isthisabox=false;
        leftChild = BVHs[0];
        rightChild = nullptr;
    } else if(BVHs.size()==2){
        isthisabox=true;
        leftChild = BVHs[0];
        rightChild = BVHs[1];
        rightChild->isthisabox=false;
        leftChild->isthisabox=false;
        leftChild->setXdim(sivelab::Vector3D(BVHs[0]->getXdim()));
        leftChild->setYdim(sivelab::Vector3D(BVHs[0]->getYdim()));
        leftChild->setZdim(sivelab::Vector3D(BVHs[0]->getZdim()));

        leftChild->xdim[1] = leftChild->xdim[2]-leftChild->xdim[0];
        leftChild->ydim[1] = leftChild->ydim[2]-leftChild->ydim[0];
        leftChild->zdim[1] = leftChild->zdim[2]-leftChild->zdim[0];

        rightChild->setXdim(sivelab::Vector3D(BVHs[1]->getXdim()));
        rightChild->setYdim(sivelab::Vector3D(BVHs[1]->getYdim()));
        rightChild->setZdim(sivelab::Vector3D(BVHs[1]->getZdim()));
        rightChild->xdim[1] = rightChild->xdim[2]-rightChild->xdim[0];
        rightChild->ydim[1] = rightChild->ydim[2]-rightChild->ydim[0];
        rightChild->zdim[1] = rightChild->zdim[2]-rightChild->zdim[0];

        minOrMax(leftChild,rightChild);


    } else{
        isthisabox=true;
        if(h == 0) std::sort(BVHs.begin(),BVHs.end());
        if(h == 1) std::sort(BVHs.begin(),BVHs.end());
        if(h == 2) std::sort(BVHs.begin(),BVHs.end());
        std::vector<Shape*> leftB(BVHs.begin(),BVHs.begin()+BVHs.size()/2);
        std::vector<Shape*> rightB((BVHs.begin()+BVHs.size()/2),BVHs.end());
        leftChild->isthisabox=true;
        rightChild->isthisabox=true;
        leftChild = new BVH(leftB,h+1);
        rightChild = new BVH(rightB,h+1);
        setValues((leftChild),leftB);
        setValues((rightChild),rightB);
        minOrMax(leftChild,rightChild);


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

bool BVH::intersect(double tminArg, double &tmaxArg, HitStruct &hit, Ray r) {
    
    double  txmin, txmax, tymin, tymax, tzmin, tzmax, txymin, txymax, txyzmax, txyzmin, tmin, tmax;
    double tHit, tNear;

    int sign[3];
    sign[0] = ((1/r.getDirection()[0]) < 0);
    sign[1] = ((1/r.getDirection()[1]) < 0);
    sign[2] = ((1/r.getDirection()[2]) < 0);

    tmin  = (bounds[sign[0]    ][0] - r.getOrigin()[0]) * (1/r.getDirection()[0]);
    tmax  = (bounds[1 - sign[0]][0] - r.getOrigin()[0]) * (1/r.getDirection()[0]);
    tymin = (bounds[sign[1]    ][1] - r.getOrigin()[1]) * (1/r.getDirection()[1]);
    tymax = (bounds[1 - sign[1]][1] - r.getOrigin()[1]) * (1/r.getDirection()[1]);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    tzmin = (bounds[sign[2]    ][2] - r.getOrigin()[2]) * (1/r.getDirection()[2]);
    tzmax = (bounds[1 - sign[2]][2] - r.getOrigin()[2]) * (1/r.getDirection()[2]);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    tHit = tmin;


    bool ifHitLeft = leftChild->intersect(tmin, tmax, hit, r);
    bool ifHitRight = rightChild->intersect(tmin,tmax, hit, r);
    bool ifHit = false;
    if((ifHitLeft)||(ifHitRight)) ifHit = true;


    return ifHit;
}



