<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Category extends Model
{
    use HasFactory;

    public function ad_categories(){
        return $this->hasMany(AdCategory::class);
    }

    public function category(){
        return $this->hasOne(Category::class);
    }
}
