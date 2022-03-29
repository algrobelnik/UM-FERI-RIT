<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Ad extends Model
{
    protected $table = 'ads';
    public $primaryKey = 'id';
    public $timestamps = true;

    public function user(){
        return $this->belongsTo(User::class);
    }

    public function images(){
        return $this->hasMany(Image::class);
    }

    public function comments(){
        return $this->hasMany(Comment::class);
    }

    public function ad_categories(){
        return $this->hasMany(AdCategory::class);
    }
}
