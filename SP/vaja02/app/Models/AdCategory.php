<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class AdCategory extends Model
{
    protected $table = 'ad_categories';
    public $primaryKey = 'id';
    public $timestamps = true;


    public function ad(){
        return $this->belongsTo(Ad::class);
    }
    public function category(){
        return $this->belongsTo(Category::class);
    }
}
