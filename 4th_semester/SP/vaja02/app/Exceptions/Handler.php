<?php

namespace App\Exceptions;

use Exception;
use Illuminate\Database\Eloquent\ModelNotFoundException;
use Illuminate\Foundation\Exceptions\Handler as ExceptionHandler;
use Illuminate\Http\JsonResponse;
use Illuminate\Http\Response;
use Throwable;

class Handler extends ExceptionHandler
{
    /**
     * A list of the exception types that are not reported.
     *
     * @var array<int, class-string<Throwable>>
     */
    protected $dontReport = [
        //
    ];

    /**
     * A list of the inputs that are never flashed for validation exceptions.
     *
     * @var array<int, string>
     */
    protected $dontFlash = [
        'current_password',
        'password',
        'password_confirmation',
    ];

    /**
     * Register the exception handling callbacks for the application.
     *
     * @return void
     */
    public function register()
    {
        $this->reportable(function (Throwable $e) {
            //
        });
    }

    /**
     * Register the exception handling callbacks for the application.
     *
     * @return JsonResponse|Response|\Symfony\Component\HttpFoundation\Response
     */
    public function render($request, Exception|Throwable $e)
    {
        // This will replace our 404 response with
        // a JSON response.
        if ($e instanceof ModelNotFoundException) {
            return response()->json([
                'error' => 'Resource not found'
            ], 404);
        }

        return parent::render($request, $e);
    }
}
